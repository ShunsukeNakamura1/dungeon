#pragma once
#include <string>

//ウインドウサイズ
#define WindowSize_X 800
#define WindowSize_Y 600

struct XY {
	int x, y;
	XY(){}
	XY(int x, int y) {
		this->x = x;
		this->y = y;
	}
	XY(char x, char y) {
		this->x = (int)x;
		this->y = (int)y;
	}
};