#include "graphics.h"

void writeRect(SDL_Renderer*, const TableInfo, int, int);

void getCoords(TableInfo& ti, draw type) {
	if (type == line) {
		cout << "First dot (x, y):" << endl;
		cin >> ti.xDot1;
		cin >> ti.yDot1;
		cout << "Second dot (x, y):" << endl;
		cin >> ti.xDot2;
		cin >> ti.yDot2;
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
	ti.xTable = 50;
	ti.yTable = 50;
	// ti.xDot1 = 17;
	// ti.yDot1 = 10;
	// ti.xDot2 = 49;
	// ti.yDot2 = 23;
	ti.xShift = ((SCREEN_wIGTH - ti.squareSize * ti.xTable) / 2);
	ti.yShift = ((SCREEN_HEIGHT - ti.squareSize * ti.yTable) / 2);
}

void writeLineCDA(const TableInfo ti, SDL_Renderer* ren) {
	int length;
	length = max(abs(ti.xDot1 - ti.xDot2), abs(ti.yDot1 - ti.yDot2));

	float dx = (float)(ti.xDot2 - ti.xDot1) / length;
	float dy = (float)(ti.yDot2 - ti.yDot1) / length;

	float x = ti.xDot1;
	float y = ti.yDot1;
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
	if (method == cda) writeLineCDA(ti, ren);
    if (method == bresenham) writeLineBresenham(ti, ren);
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
