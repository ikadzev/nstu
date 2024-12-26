#include "graphics.h"

// Deciding what are we doing
draw_t getDrawType() {
	cout << "Choose drawing type:\n 1. Line\n 2. Circle\n 3. Triangle\n 4. Pour (Lab4)\n 5. Fill polygon" << endl;
	cout << " 6. Change CONSTS\n 7. Render and clear\n 0. Exit" << endl;
	int i;
	cin >> i;
	switch(i) {
		case 1:
			cout << "Choose line type:\n 1. CDA\n 2. Bresenham" << endl;
			cin >> i;
			switch(i) {
				case 1: return cda;
				case 2: return bresenham;
				default: return draw_t::null;
			}
		case 2: return circle;
		case 3: return triangle;
		case 4: return filling;
		case 5: return polygon;
		case 6: cout << "Nuh-uh" << endl; return draw_t::null;
		case 7: return render;
		case 0: return exiting;
		default: return draw_t::null;
	}
} 

// Swaping 2 elements (only!) in TableInfo
void swp(TableInfo& ti, int first, int second) {
	Point temp;
	if (first == 1) {
		if (second == 2) {
			temp = ti.dots[0];
			ti.dots[0] = ti.dots[1];
			ti.dots[1] = temp;
		}
		if (second == 3) {
			temp = ti.dots[0];
			ti.dots[0] = ti.dots[2];
			ti.dots[2] = temp;
		}
	} else if (first == 2) {
		temp = ti.dots[1];
		ti.dots[1] = ti.dots[2];
		ti.dots[2] = temp;
	} else cout << "Error while swaping!" << endl;
}

// Getting coordinates
void getCoords(TableInfo& ti, draw_t type) {
	int x, y;
	if ((type == cda) || (type == triangle) || (type == bresenham)) {
		cout << "First dot (x, y):" << endl;
		cin >> x;
		cin >> y;
		ti.dots.push_back(Point{x, y});
		cout << "Second dot (x, y):" << endl;
		cin >> x;
		cin >> y;
		ti.dots.push_back(Point{x, y});
		if (type == triangle) {
			cout << "Third dot (x, y):" << endl;
			cin >> x;
			cin >> y;
			ti.dots.push_back(Point{x, y});
			if (ti.dots[0].y < ti.dots[1].y) swp(ti, 1, 2);
			if (ti.dots[1].y < ti.dots[2].y) { swp(ti, 2, 3); if (ti.dots[0].y < ti.dots[1].y) swp(ti, 1, 2); }
		}
	} else if (type == circle) {
		cout << "Center (x, y):" << endl;
		cin >> x;
		cin >> y;
		ti.dots.push_back(Point{x, y});
		cout << "Radius (r):" << endl;
		cin >> ti.radius;
	} else if (type == filling) {
		cout << "Start point of filling (x, y):" << endl;
		cin >> x;
		cin >> y;
		ti.dots.push_back(Point{x, y});
	} else if (type == polygon) {
		Point first_dot;
		cout << "First dot (x, y);" << endl;
		cin >> first_dot.x;
		cin >> first_dot.y;
		ti.dots.push_back(first_dot);
		cout << "Next dot (x, y or -1):" << endl;
		cin >> x;
		cin >> y;
		while ((x != first_dot.x || y != first_dot.y) && x != -1 && y != -1) {
			ti.dots.push_back(Point{x, y});
			cout << "Next dot (x, y or -1):" << endl;
			cin >> x;
			cin >> y;
		}
	} else {
		cout << "Wrong type!" << endl;
		exit(1);
	}
	ti.shift = Point{((SCREEN_WIGTH - CELL_SIZE * TABLE_SIZE) / 2), ((SCREEN_HEIGHT - CELL_SIZE * TABLE_SIZE) / 2)};
}

// Writing line with CDA
void writeLineCDA(TableInfo& ti, SDL_Renderer* ren, int xDot1, int yDot1, int xDot2, int yDot2, int color) {
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
void writeLineBresenham(TableInfo& ti, SDL_Renderer* ren, int xDot1, int yDot1, int xDot2, int yDot2, int color) {
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
void writeLine(TableInfo& ti, draw_t method, SDL_Renderer* ren, int color) {
	if (method == cda) writeLineCDA(ti, ren, ti.dots[0].x, ti.dots[0].y, ti.dots[1].x, ti.dots[1].y, color);
    if (method == bresenham) writeLineBresenham(ti, ren, ti.dots[0].x, ti.dots[0].y, ti.dots[1].x, ti.dots[1].y, color);
	if (method == triangle) {
		writeLineCDA(ti, ren, ti.dots[0].x, ti.dots[0].y, ti.dots[1].x, ti.dots[1].y, color);
		writeLineCDA(ti, ren, ti.dots[1].x, ti.dots[1].y, ti.dots[2].x, ti.dots[2].y, color);
		writeLineCDA(ti, ren, ti.dots[0].x, ti.dots[0].y, ti.dots[2].x, ti.dots[2].y, color);
	}
}

// Generating table
void tableGen(SDL_Renderer* ren, const TableInfo ti) {
	SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
	for (int i = 0; i <= TABLE_SIZE; i++) {
		SDL_RenderDrawLine(	ren, 
							i * CELL_SIZE + ti.shift.x, 
							ti.shift.y, 
							i * CELL_SIZE + ti.shift.x, 
							TABLE_SIZE * CELL_SIZE + ti.shift.y);
	}
	for (int j = 0; j <= TABLE_SIZE; j++) {
		SDL_RenderDrawLine(	ren, 
							ti.shift.x, 
							j * CELL_SIZE + ti.shift.y, 
							TABLE_SIZE * CELL_SIZE + ti.shift.x, 
							j * CELL_SIZE + ti.shift.y);
	}
}

// Drawing rectangle in table
void writeRect(SDL_Renderer* ren, TableInfo& ti, int x, int y, int color) {
	if (x > TABLE_SIZE || y > TABLE_SIZE || x < 1 || y < 1) return;
	ti.colors[x][y] = color;
	SDL_SetRenderDrawColor(ren, color >> 16, (color >> 8) & 0xFF, color & 0xFF, SDL_ALPHA_OPAQUE);
	SDL_Rect rect = {   (x - 1) * CELL_SIZE + ti.shift.x + 1, 
                        (y - 1) * CELL_SIZE + ti.shift.y + 1, 
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
void writeCircle(SDL_Renderer* ren, TableInfo& ti, int color) {
	int x = 0, y = ti.radius, d = 3 - 2 * ti.radius;

	while (x <= y) {
        writeRect(ren, ti, ti.dots[0].x + x, TABLE_SIZE - (ti.dots[0].y + y) + 1, color);
        writeRect(ren, ti, ti.dots[0].x - x, TABLE_SIZE - (ti.dots[0].y + y) + 1, color);
        writeRect(ren, ti, ti.dots[0].x + x, TABLE_SIZE - (ti.dots[0].y - y) + 1, color);
        writeRect(ren, ti, ti.dots[0].x - x, TABLE_SIZE - (ti.dots[0].y - y) + 1, color);
        writeRect(ren, ti, ti.dots[0].x + y, TABLE_SIZE - (ti.dots[0].y + x) + 1, color);
        writeRect(ren, ti, ti.dots[0].x - y, TABLE_SIZE - (ti.dots[0].y + x) + 1, color);
        writeRect(ren, ti, ti.dots[0].x + y, TABLE_SIZE - (ti.dots[0].y - x) + 1, color);
        writeRect(ren, ti, ti.dots[0].x - y, TABLE_SIZE - (ti.dots[0].y - x) + 1, color);

        if (d <= 0) d += 4 * x + 6;
        else d += 4 * (x - y--) + 10;
        x++;
	}
}

// Filling triangle with CDA
void fillTriangle(SDL_Renderer* ren, TableInfo& ti, int color) {
	int x1, x2;
	for (int sy = ti.dots[0].y - 1; sy >= ti.dots[2].y; sy--) {
		x1 = ti.dots[0].x + (sy - ti.dots[0].y) * (ti.dots[2].x - ti.dots[0].x) / (ti.dots[2].y - ti.dots[0].y);
		if (sy > ti.dots[1].y) x2 = ti.dots[0].x + (sy - ti.dots[0].y) * (ti.dots[1].x - ti.dots[0].x) / (ti.dots[1].y - ti.dots[0].y);
		else if (ti.dots[1].y == ti.dots[2].y) x2 = ti.dots[1].x;
		else x2 = ti.dots[1].x + (sy - ti.dots[1].y) * (ti.dots[2].x - ti.dots[1].x) / (ti.dots[2].y - ti.dots[1].y);
		writeLineCDA(ti, ren, x1, sy, x2, sy, color);
	}
}

// Flood fill
void floodFill(SDL_Renderer* ren, TableInfo& ti, int x, int y, int wall_color, int flood_color) {
	if (getColor(ti, x, y) == wall_color || getColor(ti, x, y) == flood_color) return;
	// cout << getColor(ti, x, y) << " " << wall_color << " " << flood_color << endl;
	// cout << x << " " << y << endl;
	writeRect(ren, ti, x, TABLE_SIZE - y + 1, flood_color);
	if (x < TABLE_SIZE) floodFill(ren, ti, x + 1, y, wall_color, flood_color);
	if (x > 1) floodFill(ren, ti, x - 1, y, wall_color, flood_color);
	if (y < TABLE_SIZE) floodFill(ren, ti, x, y + 1, wall_color, flood_color);
	if (x > 1) floodFill(ren, ti, x, y - 1, wall_color, flood_color);
}

// Getting color from TableInfo (with diffrent coords)
int getColor(TableInfo& ti, int x, int y) { return ti.colors[x][TABLE_SIZE - y + 1]; }

// Clear color list in TableInfo
void clearColors(TableInfo& ti) {
	for (int i = 1; i < TABLE_SIZE + 1; i++) {
		for (int j = 1; j < TABLE_SIZE + 1; j++) {
			ti.colors[i][j] = 0;
		}
	}
}

void polygonFill(SDL_Renderer* ren,  TableInfo& ti, int wall_color, int flood_color) {
	int dots_count = ti.dots.size();
	int y_min = TABLE_SIZE;
	int y_max = 0;

	for (Point point : ti.dots) {
		y_min = min(y_min, point.y);
		y_max = max(y_max, point.y);
	}

	for (int y = y_min; y <= y_max; y++) {
		vector<int> inter;

		for (int i = 0; i < dots_count; i++) {
			int x1 = ti.dots[i].x;
			int y1 = ti.dots[i].y;
			int x2 = ti.dots[(i + 1) % dots_count].x;
			int y2 = ti.dots[(i + 1) % dots_count].y;

			if ((y1 <= y && y2 > y) || (y2 <= y && y1 > y)) {
				int x_inter = x1 + (y - y1) * (x2 - x1) / (y2 - y1);
				inter.push_back(x_inter);
			}
		}	

		if (inter.begin() != inter.end()) sort(inter.begin(), inter.end());
		
		for (int i = 0; i < inter.size(); i += 2) writeLineCDA(ti, ren, inter[i], y, inter[i + 1], y, flood_color);
	}
	for (int i = 1; i < dots_count; i++) {
		writeLineCDA(ti, ren, ti.dots[i - 1].x, ti.dots[i - 1].y, ti.dots[i].x, ti.dots[i].y, wall_color);
	}
	writeLineCDA(ti, ren, ti.dots[0].x, ti.dots[0].y, ti.dots[dots_count - 1].x, ti.dots[dots_count - 1].y, wall_color);
}
