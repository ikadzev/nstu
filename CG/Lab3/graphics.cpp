#include "graphics.h"

void swp(TableInfo& ti, int first, int second) {
	if (first == 1) {
		if (second == 2) {
			int t = ti.xDot1;
			ti.xDot1 = ti.xDot2;
			ti.xDot2 = t;
			t = ti.yDot1;
			ti.yDot1 = ti.yDot2;
			ti.yDot2 = t;
		}
		if (second == 3) {
			int t = ti.xDot1;
			ti.xDot1 = ti.xDot3;
			ti.xDot3 = t;
			t = ti.yDot1;
			ti.yDot1 = ti.yDot3;
			ti.yDot3 = t;
		}
	} else if (first == 2) {
		int t = ti.xDot2;
		ti.xDot2 = ti.xDot3;
		ti.xDot3 = t;
		t = ti.yDot2;
		ti.yDot2 = ti.yDot3;
		ti.yDot3 = t;
	} else cout << "Error while swaping!" << endl;
}

void getCoords(TableInfo& ti, draw type) {
	if ((type == line) || (type == triangle)) {
		cout << "First dot (x, y):" << endl;
		cin >> ti.xDot1;
		cin >> ti.yDot1;
		cout << "Second dot (x, y):" << endl;
		cin >> ti.xDot2;
		cin >> ti.yDot2;
		if (type == triangle) {
			cout << "Third dot (x, y):" << endl;
			cin >> ti.xDot3;
			cin >> ti.yDot3;
			if (ti.yDot1 < ti.yDot2) swp(ti, 1, 2);
			if (ti.yDot2 < ti.yDot3) { swp(ti, 2, 3); if (ti.yDot1 < ti.yDot2) swp(ti, 1, 2); }
		}
	} else if (type == circle) {
		cout << "Center (x, y):" << endl;
		cin >> ti.xDot1;
		cin >> ti.yDot1;
		cout << "Radius (r):" << endl;
		cin >> ti.radius;
	} else {
		cout << "Wrong type!" << endl;
		exit(1);
	}
	ti.squareSize = CELL_SIZE;
	ti.xTable = TABLE_SIZE;
	ti.yTable = TABLE_SIZE;
	ti.xShift = ((SCREEN_wIGTH - ti.squareSize * ti.xTable) / 2);
	ti.yShift = ((SCREEN_HEIGHT - ti.squareSize * ti.yTable) / 2);
}

void writeLineCDA(const TableInfo ti, SDL_Renderer* ren, int xDot1, int yDot1, int xDot2, int yDot2) {
	int length = max(abs(xDot1 - xDot2), abs(yDot1 - yDot2));

	float dx = (float)(xDot2 - xDot1) / length;
	float dy = (float)(yDot2 - yDot1) / length;

	float x = xDot1;
	float y = yDot1;
	int i = 0;
	while (i <= length) {
		writeRect(ren, ti, round(x), round(ti.yTable - y + 1));
		x += dx;
		y += dy;
		i++;
	}
}

void writeLineBresenham(const TableInfo ti, SDL_Renderer* ren) {
	int dx, dy, ch = 0, i = 0, e, dx2, dy2;
	int x = ti.xDot1, y = ti.yDot1;
	
	dx = abs(ti.xDot2 - ti.xDot1); 
	
	dy = abs(ti.yDot2 - ti.yDot1); 
	if (!dx && !dy) return;
	int sx, sy;
	if (dx) sx = (ti.xDot2 - ti.xDot1) < 0 ? -1 : 1; 
	if (dx) sy = (ti.yDot2 - ti.yDot1) < 0 ? -1 : 1; 

	if (dy > dx) { 
		int t = dy; dy = dx; dx = t; ch = 1; 
	}
	dx2 = dx << 1;
	dy2 = dy << 1;
	e = dy2 - dx; 
	while ((x != ti.xDot2) && (y != ti.yDot2)) {
		writeRect(ren, ti, x, ti.yTable - y + 1);
		if (e > 0) { 
			if (ch) {
				x += sx;
			}
			else {
 				y += sy;
			}
			e -= dx2;
		}
		else { 
			if (ch) {
				y += sy;
			}
			else {
				x += sx;
			}
			e += dy2;
		}
	}
}

void writeLine(const TableInfo ti, line_t method, SDL_Renderer* ren) {
	if (method == cda) writeLineCDA(ti, ren, ti.xDot1, ti.yDot1, ti.xDot2, ti.yDot2);
    if (method == bresenham) writeLineBresenham(ti, ren);
	if (method == trngl) {
		writeLineCDA(ti, ren, ti.xDot1, ti.yDot1, ti.xDot2, ti.yDot2);
		writeLineCDA(ti, ren, ti.xDot2, ti.yDot2, ti.xDot3, ti.yDot3);
		writeLineCDA(ti, ren, ti.xDot1, ti.yDot1, ti.xDot3, ti.yDot3);
	}
}

void tableGen(SDL_Renderer* ren, const TableInfo ti) {
	SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
	for (int i = 0; i <= ti.xTable; i++) {
		SDL_RenderDrawLine(	ren, 
							i * ti.squareSize + ti.xShift, 
							ti.yShift, 
							i * ti.squareSize + ti.xShift, 
							ti.yTable * ti.squareSize + ti.yShift);
	}
	for (int j = 0; j <= ti.yTable; j++) {
		SDL_RenderDrawLine(	ren, 
							ti.xShift, 
							j * ti.squareSize + ti.yShift, 
							ti.xTable * ti.squareSize + ti.xShift, 
							j * ti.squareSize + ti.yShift);
	}
}

void writeRect(SDL_Renderer* ren, const TableInfo ti, int x, int y) {
	if (x > ti.xTable || y > ti.yTable || x < 1 || y < 1) return;
	SDL_SetRenderDrawColor(ren, 0, 128, 128, 255);
	SDL_Rect rect = {   (x - 1) * ti.squareSize + ti.xShift + 1, 
                        (y - 1) * ti.squareSize + ti.yShift + 1, 
                        ti.squareSize - 1, 
                        ti.squareSize -1};
	SDL_RenderFillRect(ren, &rect);
}

void endSDL(SDL_Window* win, SDL_Renderer* ren) {
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	SDL_Quit();
}

void writeCircle(SDL_Renderer* ren, const TableInfo ti) {
	int x = 0, y = ti.radius, d = 3 - 2 * ti.radius;

	while (x <= y) {
        writeRect(ren, ti, ti.xDot1 + x, ti.yTable - (ti.yDot1 + y) + 1);
        writeRect(ren, ti, ti.xDot1 - x, ti.yTable - (ti.yDot1 + y) + 1);
        writeRect(ren, ti, ti.xDot1 + x, ti.yTable - (ti.yDot1 - y) + 1);
        writeRect(ren, ti, ti.xDot1 - x, ti.yTable - (ti.yDot1 - y) + 1);
        writeRect(ren, ti, ti.xDot1 + y, ti.yTable - (ti.yDot1 + x) + 1);
        writeRect(ren, ti, ti.xDot1 - y, ti.yTable - (ti.yDot1 + x) + 1);
        writeRect(ren, ti, ti.xDot1 + y, ti.yTable - (ti.yDot1 - x) + 1);
        writeRect(ren, ti, ti.xDot1 - y, ti.yTable - (ti.yDot1 - x) + 1);

        if (d <= 0) d += 4 * x + 6;
        else d += 4 * (x - y--) + 10;
        x++;
	}
}

void writeTriangle(SDL_Renderer* ren, const TableInfo ti) {
	writeLine(ti, trngl, ren);
	int x1, x2;
	for (int sy = ti.yDot1 - 1; sy >= ti.yDot3; sy--) {
		x1 = ti.xDot1 + (sy - ti.yDot1) * (ti.xDot3 - ti.xDot1) / (ti.yDot3 - ti.yDot1);
		if (sy > ti.yDot2) x2 = ti.xDot1 + (sy - ti.yDot1) * (ti.xDot2 - ti.xDot1) / (ti.yDot2 - ti.yDot1);
		else if (ti.yDot2 == ti.yDot3) x2 = ti.xDot2;
		else x2 = ti.xDot2 + (sy - ti.yDot2) * (ti.xDot3 - ti.xDot2) / (ti.yDot3 - ti.yDot2);
		writeLineCDA(ti, ren, x1, sy, x2, sy);
	}
}