#pragma once
#include <string>

//�E�C���h�E�T�C�Y
#define WindowSize_X 800
#define WindowSize_Y 600
//�v���C���[�摜�̃t�@�C����
#define PLAYER_GRAPH "Resource/graph/player.png"
//�X�e�[�W�摜�̃t�@�C����
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