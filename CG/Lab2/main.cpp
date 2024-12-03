#include <iostream>
#include <windows.h>
#include <windowsx.h>
using namespace std;

constexpr auto CELL_SIZE = 30;

void getCoords(int& x, int& y, int& xDot1, int& yDot1, int& xDot2, int& yDot2) {
	/*cout << "Grid (x, y):" << endl;
	cin >> x;
	cin >> y;
	cout << "First dot (x, y):" << endl;
	cin >> xDot1;
	cin >> yDot1;
	cout << "Second dot (x, y):" << endl;
	cin >> xDot2;
	cin >> yDot2;*/
	x = 10;
	y = 10;
	xDot1 = 1;
	yDot1 = 2;
	xDot2 = 9;
	yDot2 = 9;
}

void getConsole(HWND& hwnd, HDC& hdc) {
	hwnd = GetConsoleWindow();
	hdc = GetDC(hwnd);
}

void getBrushes(HBRUSH& blackBrush, HPEN& whitePen, HBRUSH& blueBrush) {
	blackBrush = GetStockBrush(BLACK_BRUSH);
	whitePen = GetStockPen(WHITE_PEN);
	blueBrush = CreateSolidBrush(RGB(0, 0, 255));
}

void tableLines() {}

void tableGen(HDC hdc, int x, int y) {
	for (int i = 0; i <= x; i++) {
		LineTo(hdc, i * CELL_SIZE, y * CELL_SIZE);
		MoveToEx(hdc, (i + 1) * CELL_SIZE, 0, NULL);
	}
	MoveToEx(hdc, 0, 0, NULL);
	for (int j = 0; j <= y; j++) {
		LineTo(hdc, x * CELL_SIZE, j * CELL_SIZE);
		MoveToEx(hdc, 0, (j + 1) * CELL_SIZE, NULL);
	}
}

void writeRect(HDC hdc, int xDot, int yDot) {
	int xDotCoord = (xDot - 1) * CELL_SIZE;
	int yDotCoord = (yDot - 1) * CELL_SIZE;
	Rectangle(hdc, xDotCoord, yDotCoord, xDotCoord + CELL_SIZE, yDotCoord + CELL_SIZE);
}

void initTable(HDC hdc, HBRUSH brush, HPEN pen) {
	SelectBrush(hdc, brush);
	FloodFill(hdc, 0, 0, RGB(0, 0, 1));
	SelectPen(hdc, pen);
	MoveToEx(hdc, 0, 0, NULL);
}

void endConsole(HWND hwnd, HDC hdc, HPEN pen) {
	DeleteObject(pen);
	ReleaseDC(hwnd, hdc);
}

void writeLineCDA(int xTable, int yTable, int xDot1, int yDot1, int xDot2, int yDot2, HDC hdc) {
	int length;
	length = max(abs(xDot1 - xDot2), abs(yDot1 - yDot2));

	float dx = (float)(xDot2 - xDot1) / length;
	float dy = (float)(yDot2 - yDot1) / length;

	float x = xDot1;
	float y = yDot1;
	int i = 0;
	while (i <= length) {
		if ((x <= xTable) && (y <= yTable)) writeRect(hdc, x, round(yTable - y + 1));
		x += dx;
		y += dy;
		i++;
	}
}

void writeLineBresenham(int xTable, int yTable, int xDot1, int yDot1, int xDot2, int yDot2, HDC hdc) {
	int dx, dy, ch = 0, i = 0, e, dx2, dy2;

	xDot2 -= xDot1; 
	dx = abs(xDot2);
	yDot2 -= yDot1; 
	dy = abs(yDot2);
	if (!xDot2 && !yDot2) return;
	if (xDot2) xDot2 = xDot2 < 0 ? -1 : 1;
	if (yDot2) yDot2 = yDot2 < 0 ? -1 : 1;

	if (dy > dx) { 
		int t = dy; dy = dx; dx = t; ch = 1; 
	}
	dx2 = dx << 1; 
	dy2 = dy << 1;
	e = dy2 - dx;
	for (i = 0; i < dx; ++i) {
		if ((xDot1 <= xTable) && (yDot1 <= yTable)) writeRect(hdc, xDot1, round(yTable - yDot1 + 1));
		if (e > 0) { 
			if (ch) {
				xDot1 += xDot2;
			}
			else {
				yDot1 += yDot2;
			}
			e -= dx2; 
		}
		else { 
			if (ch) {
				yDot1 += yDot2;
			}
			else {
				xDot1 += xDot2;
			}
			e += dy2;
		}
	}
}

void writeLine(int x, int y, int xDot1, int yDot1, int xDot2, int yDot2, int method, HDC hdc) {
	switch (method) {
	case 1:
		writeLineCDA(x, y, xDot1, yDot1, xDot2, yDot2, hdc);
		break;
	case 2:
		writeLineBresenham(x, y, xDot1, yDot1, xDot2, yDot2, hdc);
		break;
	}
}

int main()
{
	int xTable, yTable, xDot1, yDot1, xDot2, yDot2;
	getCoords(xTable, yTable, xDot1, yDot1, xDot2, yDot2);

	HWND hwnd; HDC hdc; HBRUSH blackBrush, blueBrush; HPEN whitePen;
	getConsole(hwnd, hdc);
	getBrushes(blackBrush, whitePen, blueBrush);

	initTable(hdc, blackBrush, whitePen);
	tableGen(hdc, xTable, yTable);

	SelectBrush(hdc, blueBrush);

	writeLine(xTable, yTable, xDot1, yDot1, xDot2, yDot2, 2, hdc);

	int smth;
	cin >> smth;

	endConsole(hwnd, hdc, whitePen);
	return 0;
}