#include <iostream>
#include <SDL2/SDL.h>
using namespace std;

constexpr int CELL_SIZE = 11;
constexpr int SCREEN_wIGTH = 1920;
constexpr int SCREEN_HEIGHT = 1200;

typedef struct TableInfo {
	int squareSize;
	int xTable;
	int yTable;
	int xShift;
	int yShift;
	int radius;
	int xDot1;
	int yDot1;
	int xDot2;
	int yDot2;
} TableInfo;

enum draw {
	circle,
	line
};

enum line_t {
    cda,
    bresenham
};

void writeRect(SDL_Renderer*, const TableInfo, int, int);
void getCoords(TableInfo&, draw);
void writeLineCDA(const TableInfo, SDL_Renderer*);
void writeLineBresenham(const TableInfo, SDL_Renderer*);
void writeLine(const TableInfo, line_t, SDL_Renderer*);
void tableGen(SDL_Renderer*, const TableInfo);
void writeRect(SDL_Renderer*, const TableInfo, int, int);
void endSDL(SDL_Window*, SDL_Renderer*);
void writeCircle(SDL_Renderer*, const TableInfo);