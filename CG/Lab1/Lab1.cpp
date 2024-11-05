#include <iostream>
#include <windows.h>
#include <windowsx.h>

using namespace std;

void getCoords(int& x, int& y, int& xDot, int& yDot) {
	cin >> x;
	cin >> y;
	cin >> xDot;
	cin >> yDot;
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
		LineTo(hdc, i * 50, y * 50);
		MoveToEx(hdc, (i + 1) * 50, 0, NULL);
	}
	MoveToEx(hdc, 0, 0, NULL);
	for (int j = 0; j <= y; j++) {
		LineTo(hdc, x * 50, j * 50);
		MoveToEx(hdc, 0, (j + 1) * 50, NULL);
	}
}

void writeRect(HDC hdc, int xDot, int yDot) {
	int xDotCoord = (xDot - 1) * 50;
	int yDotCoord = (yDot - 1) * 50;
	Rectangle(hdc, xDotCoord, yDotCoord, xDotCoord + 50, yDotCoord + 50);
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

int main()
{
	int x, y, xDot, yDot;
	getCoords(x, y, xDot, yDot);

	HWND hwnd; HDC hdc; HBRUSH blackBrush, blueBrush; HPEN whitePen;
	getConsole(hwnd, hdc);
	getBrushes(blackBrush, whitePen, blueBrush);

	initTable(hdc, blackBrush, whitePen);
	tableGen(hdc, x, y);

	SelectBrush(hdc, blueBrush);
	if ((xDot <= x) && (yDot <= y)) { writeRect(hdc, xDot, y - yDot + 1); }

	int i;
	cin >> i;

	endConsole(hwnd, hdc, whitePen);
	return 0;
}