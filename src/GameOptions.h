#pragma once
#include <string>

//ウインドウサイズ
#define WindowSize_X 800
#define WindowSize_Y 600
//プレイヤー画像のファイル名
#define PLAYER_GRAPH "Resource/graph/player.png"
//ステージ画像のファイル名
#define STAGE1_GRAPH "Resource/graph/floor_wall.png"


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
	XY operator+(XY xy2) {
		return XY(x + xy2.x, y + xy2.y);
	}
};