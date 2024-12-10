#include <iostream>
#include <SDL2/SDL.h>
using namespace std;

constexpr auto CELL_SIZE = 30;
constexpr int SCREEN_wIGTH = 1920;
constexpr int SCREEN_HEIGHT = 1200;

typedef struct TableInfo {
	int squareSize;
	int xTable;
	int yTable;
	int xDot1;
	int yDot1;
	int xDot2;
	int yDot2;
	int xShift;
	int yShift;
} TableInfo;

void writeRect(SDL_Renderer*, const TableInfo, int, int);

void getCoords(TableInfo& ti) {
	/*cout << "Grid (x, y):" << endl;
	cin >> ti.xTable;
	cin >> ti.yTable;
	cout << "First dot (x, y):" << endl;
	cin >> ti.xDot1;
	cin >> ti.yDot1;
	cout << "Second dot (x, y):" << endl;
	cin >> ti.xDot2;
	cin >> ti.yDot2;*/
	ti.squareSize = 20;
	ti.xTable = 30;
	ti.yTable = 30;
	ti.xDot1 = 14;
	ti.yDot1 = 3;
	ti.xDot2 = 7;
	ti.yDot2 = 27;
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
		if ((x <= ti.xTable) && (y <= ti.yTable)) writeRect(ren, ti, round(x), round(ti.yTable - y + 1));
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
		if ((x <= ti.xTable) && (y <= ti.yTable)) writeRect(ren, ti, x, ti.yTable - y + 1);
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

void writeLine(const TableInfo ti, int method, SDL_Renderer* ren) {
	switch (method) {
	case 1:
		writeLineCDA(ti, ren);
		break;
	case 2:
		writeLineBresenham(ti, ren);
		break;
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
	SDL_SetRenderDrawColor(ren, 0, 128, 128, 255);
	SDL_Rect rect = {(x - 1) * ti.squareSize + ti.xShift + 1, (y - 1) * ti.squareSize + ti.yShift + 1, ti.squareSize - 1, ti.squareSize -1};
	SDL_RenderFillRect(ren, &rect);
}

void endSDL(SDL_Window* win, SDL_Renderer* ren) {
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	SDL_Quit();
}


int main()
{
	TableInfo ti;
	getCoords(ti);

	if (SDL_Init(SDL_INIT_VIDEO)) exit(101);
	SDL_Window* win = SDL_CreateWindow("SDL Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1980, 1200, SDL_WINDOW_FULLSCREEN);
	if (!win) {
		SDL_Quit();
		exit(102);
	}
	
	SDL_Renderer* ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
	if (!ren) {
		SDL_DestroyWindow(win);
		SDL_Quit();
		exit(103);
	}
	SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
	SDL_RenderClear(ren);

	tableGen(ren, ti);
	writeLine(ti, 1, ren);
	SDL_RenderPresent(ren);

	int nipaa;
	cin >> nipaa;

	endSDL(win, ren);
	return 0;
}