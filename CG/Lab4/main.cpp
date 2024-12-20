#include "graphics.h"

int main() {
	cout << "Current CONSTS:" << endl;
	cout << "CELL_SIZE " << CELL_SIZE << endl;
	cout << "TABLE_SIZE " << TABLE_SIZE << endl;
	cout << "SCREEN_SIZE " << SCREEN_WIGTH << " x " << SCREEN_HEIGHT << endl;

	draw_t draw_type = draw_t::null;
	while (draw_type == draw_t::null) draw_type = getDrawType();
	TableInfo ti;
	getCoords(ti, draw_type);

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
	if (draw_type == cda || draw_type == bresenham)
		writeLine(ti, draw_type, ren, 0xffcb47);
	if (draw_type == triangle) { 
		fillTriangle(ren, ti, 0xffc564, 0x860202);
		writeLine(ti, draw_type, ren, 0xffcb47);
	}
	if (draw_type == circle) writeCircle(ren, ti, 0xffcb47);
	SDL_RenderPresent(ren);

	bool running = true;
	SDL_Event event;
	while (running) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE) running = false;
		}
	}

	endSDL(win, ren);
	return 0;
}