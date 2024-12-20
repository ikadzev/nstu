#include <iostream>
#include <SDL2/SDL.h>
using namespace std;

constexpr int CELL_SIZE = 20; // Cell size in pixels
constexpr int TABLE_SIZE = 50; // Table size in cells
constexpr int SCREEN_WIGTH = 1920; // Screen wight
constexpr int SCREEN_HEIGHT = 1200; // Screen height

// Speaks for itself. 
// Contains dots coords, radius for circle (center in first dot) and table shift.
typedef struct TableInfo {
	int xShift; 
	int yShift;
	int radius;
	int xFill;
	int yFill;
	int xDot1;
	int yDot1;
	int xDot2;
	int yDot2;
	int xDot3;
	int yDot3;
} TableInfo;

// Drawing type
enum draw_t {
	null,
	cda,
	bresenham,
	circle,
	triangle,
	filling
};

draw_t getDrawType();
void getCoords(TableInfo&, draw_t);
void writeLineCDA(const TableInfo, SDL_Renderer*, int, int, int, int, int);
void writeLineBresenham(const TableInfo, SDL_Renderer*, int, int, int, int, int);
void writeLine(const TableInfo, draw_t, SDL_Renderer*, int);
void tableGen(SDL_Renderer*, const TableInfo);
void writeRect(SDL_Renderer*, const TableInfo, int, int, int);
void endSDL(SDL_Window*, SDL_Renderer*);
void writeCircle(SDL_Renderer*, const TableInfo, int);
void fillTriangle(SDL_Renderer*, const TableInfo, int, int);