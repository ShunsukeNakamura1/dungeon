#pragma once
#include <DxLib.h>

/*�L�����N�^�[���
char[] name     :���O
char   level    :���x��
char   xpos,ypos:���W
*/
struct CHARACTER {
	char name[32];
	char ID;
	char level;
	char xpos, ypos;
	int CharGraph;
	int exp;
};
extern CHARACTER player;

