#include <iostream>
#include <SDL2/SDL.h>
#include <vector>
#include <algorithm>
using namespace std;

constexpr int CELL_SIZE = 20; // Cell size in pixels
constexpr int TABLE_SIZE = 50; // Table size in cells
constexpr int SCREEN_WIGTH = 1100; // Screen wight
constexpr int SCREEN_HEIGHT = 1100; // Screen height
constexpr int WALL_COLOR = 0xFFCB47;
constexpr int FLOOD_COLOR = 0x860202;

// Finally, structure for point
struct Point {
	int x;
	int y;
};

// Speaks for itself. 
// Contains dots coords, radius for circle (center in first dot) and table shift.
typedef struct TableInfo {
	int colors[TABLE_SIZE + 1][TABLE_SIZE + 1];
	Point shift;
	int radius;
	vector<Point> dots;
} TableInfo;

// Drawing type
enum draw_t {
	null,
	cda,
	bresenham,
	circle,
	triangle,
	filling,
	render,
	polygon,
	exiting
};

draw_t getDrawType();
void getCoords(TableInfo&, draw_t);
void writeLineCDA(TableInfo&, SDL_Renderer*, int, int, int, int, int);
void writeLineBresenham(TableInfo&, SDL_Renderer*, int, int, int, int, int);
void writeLine(TableInfo&, draw_t, SDL_Renderer*, int);
void tableGen(SDL_Renderer*, const TableInfo);
void writeRect(SDL_Renderer*, TableInfo&, int, int, int);
void endSDL(SDL_Window*, SDL_Renderer*);
void writeCircle(SDL_Renderer*, TableInfo&, int);
void fillTriangle(SDL_Renderer*, TableInfo&, int);
void floodFill(SDL_Renderer* ren, TableInfo& ti, int x, int y, int wall_color, int flood_color);
int getColor(TableInfo& ti, int x, int y);
void clearColors(TableInfo&);
void polygonFill(SDL_Renderer* ren,  TableInfo& ti, int wall_color, int flood_color);