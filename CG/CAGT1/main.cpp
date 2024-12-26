#include "graphics.h"

int main() {
	cout << "Current CONSTS:" << endl;
	cout << "CELL_SIZE " << CELL_SIZE << endl;
	cout << "TABLE_SIZE " << TABLE_SIZE << endl;
	cout << "SCREEN_SIZE " << SCREEN_WIGTH << " x " << SCREEN_HEIGHT << endl;

	draw_t draw_type = draw_t::null; TableInfo ti;
	clearColors(ti);

	if (SDL_Init(SDL_INIT_VIDEO)) exit(101);
	SDL_Window* win = SDL_CreateWindow("SDL Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIGTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
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

	bool running = true;
	while (running) {
		while (draw_type == draw_t::null) draw_type = getDrawType();
		if (draw_type != render && draw_type != exiting) getCoords(ti, draw_type);
		tableGen(ren, ti);
		switch (draw_type) {
			case triangle:
			case cda:
			case bresenham:
				writeLine(ti, draw_type, ren, WALL_COLOR);
				break;
			case circle:
				writeCircle(ren, ti, WALL_COLOR);
				break;
			case filling:
				floodFill(ren, ti, ti.dots[0].x, ti.dots[0].y, WALL_COLOR, FLOOD_COLOR);
				break;
			case polygon:
				polygonFill(ren, ti, WALL_COLOR, FLOOD_COLOR);
				break;
			case render:
				SDL_RenderPresent(ren);
				SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
				SDL_RenderClear(ren);
				clearColors(ti);
				break;
			case exiting:
				running = false;
		}
		draw_type = draw_t::null;
		ti.dots.clear();
	}
	
	endSDL(win, ren);
	return 0;
}