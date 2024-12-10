#include "graphics.h"

int main() {
	draw type = circle;
	line_t line_type = cda;
	//
	// INIT CONSTS
	//

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
	
	TableInfo ti;
	getCoords(ti, type);

	tableGen(ren, ti);
	if (type == line) writeLine(ti, line_type, ren);
	if (type == circle) writeCircle(ren, ti);
	SDL_RenderPresent(ren);

	int nipaa;
	cin >> nipaa;

	endSDL(win, ren);
	return 0;
}