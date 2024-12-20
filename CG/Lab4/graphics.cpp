#include "graphics.h"

// Deciding what are we doing
draw_t getDrawType() {
	cout << "Choose drawing type:\n 1. Line\n 2. Circle\n 3. Triangle\n 4. Fill\n 5. Change CONSTS\n 0. Exit" << endl;
	int i;
	cin >> i;
	switch(i) {
		case 2: return circle;
		case 3: return triangle;
		case 4: return filling;
		case 5: cout << "Nuh-uh" << endl; return draw_t::null;
		case 0: exit(0);
		case 1:
			cout << "Choose line type:\n 1. CDA\n 2. Bresenham" << endl;
			cin >> i;
			switch(i) {
				case 1: return cda;
				case 2: return bresenham;
				default: return draw_t::null;
			}
		default: return draw_t::null;
	}
} 

// Swaping 2 elements (only!) in TableInfo
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

// Getting coordinates
void getCoords(TableInfo& ti, draw_t type) {
	if ((type == cda) || (type == triangle) || (type == bresenham)) {
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
	} else if (type == filling) {
		cout << "Start point of filling (x, y):" << endl;
		cin >> ti.xFill;
		cin >> ti.yFill;
	} else {
		cout << "Wrong type!" << endl;
		exit(1);
	}
	ti.xShift = ((SCREEN_WIGTH - CELL_SIZE * TABLE_SIZE) / 2);
	ti.yShift = ((SCREEN_HEIGHT - CELL_SIZE * TABLE_SIZE) / 2);
}

// Writing line with CDA
void writeLineCDA(const TableInfo ti, SDL_Renderer* ren, int xDot1, int yDot1, int xDot2, int yDot2, int color) {
	int length = max(abs(xDot1 - xDot2), abs(yDot1 - yDot2));

	float dx = (float)(xDot2 - xDot1) / length;
	float dy = (float)(yDot2 - yDot1) / length;

	float x = xDot1;
	float y = yDot1;
	int i = 0;
	while (i <= length) {
		writeRect(ren, ti, round(x), round(TABLE_SIZE - y + 1), color);
		x += dx;
		y += dy;
		i++;
	}
}

// Writing line with Brezenham
void writeLineBresenham(const TableInfo ti, SDL_Renderer* ren, int xDot1, int yDot1, int xDot2, int yDot2, int color) {
	int dx, dy, ch = 0, i = 0, e, dx2, dy2;
	int x = xDot1, y = yDot1;
	
	dx = abs(xDot2 - xDot1); 
	
	dy = abs(yDot2 - yDot1); 
	if (!dx && !dy) return;
	int sx, sy;
	if (dx) sx = (xDot2 - xDot1) < 0 ? -1 : 1; 
	if (dx) sy = (yDot2 - yDot1) < 0 ? -1 : 1; 

	if (dy > dx) { 
		int t = dy; dy = dx; dx = t; ch = 1; 
	}
	dx2 = dx << 1;
	dy2 = dy << 1;
	e = dy2 - dx; 
	while ((x != xDot2) && (y != yDot2)) {
		writeRect(ren, ti, x, TABLE_SIZE - y + 1, color);
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

// Drawing line with method in draw_t
void writeLine(const TableInfo ti, draw_t method, SDL_Renderer* ren, int color) {
	if (method == cda) writeLineCDA(ti, ren, ti.xDot1, ti.yDot1, ti.xDot2, ti.yDot2, color);
    if (method == bresenham) writeLineBresenham(ti, ren, ti.xDot1, ti.yDot1, ti.xDot2, ti.yDot2, color);
	if (method == triangle) {
		writeLineCDA(ti, ren, ti.xDot1, ti.yDot1, ti.xDot2, ti.yDot2, color);
		writeLineCDA(ti, ren, ti.xDot2, ti.yDot2, ti.xDot3, ti.yDot3, color);
		writeLineCDA(ti, ren, ti.xDot1, ti.yDot1, ti.xDot3, ti.yDot3, color);
	}
}

// Generating table
void tableGen(SDL_Renderer* ren, const TableInfo ti) {
	SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
	for (int i = 0; i <= TABLE_SIZE; i++) {
		SDL_RenderDrawLine(	ren, 
							i * CELL_SIZE + ti.xShift, 
							ti.yShift, 
							i * CELL_SIZE + ti.xShift, 
							TABLE_SIZE * CELL_SIZE + ti.yShift);
	}
	for (int j = 0; j <= TABLE_SIZE; j++) {
		SDL_RenderDrawLine(	ren, 
							ti.xShift, 
							j * CELL_SIZE + ti.yShift, 
							TABLE_SIZE * CELL_SIZE + ti.xShift, 
							j * CELL_SIZE + ti.yShift);
	}
}

// Drawing rectangle in table
void writeRect(SDL_Renderer* ren, const TableInfo ti, int x, int y, int color) {
	if (x > TABLE_SIZE || y > TABLE_SIZE || x < 1 || y < 1) return;
	SDL_SetRenderDrawColor(ren, color >> 16, (color >> 8) & 0xFF, color & 0xFF, SDL_ALPHA_OPAQUE);
	SDL_Rect rect = {   (x - 1) * CELL_SIZE + ti.xShift + 1, 
                        (y - 1) * CELL_SIZE + ti.yShift + 1, 
                        CELL_SIZE - 1, 
                        CELL_SIZE -1};
	SDL_RenderFillRect(ren, &rect);
}

// Destroying SDL_Window and SDL_Renderer
void endSDL(SDL_Window* win, SDL_Renderer* ren) {
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	SDL_Quit();
}

// Writing circle with Bresenham
void writeCircle(SDL_Renderer* ren, const TableInfo ti, int color) {
	int x = 0, y = ti.radius, d = 3 - 2 * ti.radius;

	while (x <= y) {
        writeRect(ren, ti, ti.xDot1 + x, TABLE_SIZE - (ti.yDot1 + y) + 1, color);
        writeRect(ren, ti, ti.xDot1 - x, TABLE_SIZE - (ti.yDot1 + y) + 1, color);
        writeRect(ren, ti, ti.xDot1 + x, TABLE_SIZE - (ti.yDot1 - y) + 1, color);
        writeRect(ren, ti, ti.xDot1 - x, TABLE_SIZE - (ti.yDot1 - y) + 1, color);
        writeRect(ren, ti, ti.xDot1 + y, TABLE_SIZE - (ti.yDot1 + x) + 1, color);
        writeRect(ren, ti, ti.xDot1 - y, TABLE_SIZE - (ti.yDot1 + x) + 1, color);
        writeRect(ren, ti, ti.xDot1 + y, TABLE_SIZE - (ti.yDot1 - x) + 1, color);
        writeRect(ren, ti, ti.xDot1 - y, TABLE_SIZE - (ti.yDot1 - x) + 1, color);

        if (d <= 0) d += 4 * x + 6;
        else d += 4 * (x - y--) + 10;
        x++;
	}
}

// Filling triangle with CDA
void fillTriangle(SDL_Renderer* ren, const TableInfo ti, int color1, int color2) {
	int x1, x2;
	for (int sy = ti.yDot1 - 1; sy >= ti.yDot3; sy--) {
		x1 = ti.xDot1 + (sy - ti.yDot1) * (ti.xDot3 - ti.xDot1) / (ti.yDot3 - ti.yDot1);
		if (sy > ti.yDot2) x2 = ti.xDot1 + (sy - ti.yDot1) * (ti.xDot2 - ti.xDot1) / (ti.yDot2 - ti.yDot1);
		else if (ti.yDot2 == ti.yDot3) x2 = ti.xDot2;
		else x2 = ti.xDot2 + (sy - ti.yDot2) * (ti.xDot3 - ti.xDot2) / (ti.yDot3 - ti.yDot2);
		writeLineCDA(ti, ren, x1, sy, x2, sy, color2);
		SDL_Delay(200);
		SDL_RenderPresent(ren);
	}
}

void floodFill(SDL_Renderer* ren, const TableInfo ti, int x, int y, int wall_color, int flood_colort) {

}

