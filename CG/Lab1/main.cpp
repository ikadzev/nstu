#include <iostream>
#include <SDL2/SDL.h>
// #include <windows.h>
// #include <windowsx.h>

using namespace std;

void getCoords(int& x, int& y, int& xDot, int& yDot) {
	// cin >> x;
	// cin >> y;
	// cin >> xDot;
	// cin >> yDot;
	x = 10;
	y = 8;
	xDot = 6;
	yDot = 3;
}

void tableGen(SDL_Renderer* ren, int x, int y) {
	SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
	for (int i = 0; i <= x; i++) {
		SDL_RenderDrawLine(ren, i * 50, 0, i * 50, y * 50);
	}
	for (int j = 0; j <= y; j++) {
		SDL_RenderDrawLine(ren, 0, j * 50, x * 50, j * 50);
	}
}

void writeRect(SDL_Renderer* ren, int x, int y) {
	SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
	SDL_Rect rect = {(x - 1) * 50, (y - 1) * 50, 50, 50};
	SDL_RenderFillRect(ren, &rect);
}

void endSDL(SDL_Window* win, SDL_Renderer* ren) {
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	SDL_Quit();
}

int main()
{
	int x, y, xDot, yDot;
	getCoords(x, y, xDot, yDot);

	if (SDL_Init(SDL_INIT_VIDEO)) exit(101);
	SDL_Window* win = SDL_CreateWindow("SDL Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 900, 900, SDL_WINDOW_SHOWN);
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

	tableGen(ren, x, y);
	if ((xDot <= x) && (yDot <= y)) writeRect(ren, xDot, y - yDot + 1);
	SDL_RenderPresent(ren);

	int i;
	cin >> i;

	endSDL(win, ren);
	return 0;
}