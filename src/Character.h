#pragma once
#include <DxLib.h>

/*キャラクター情報
char[] name     :名前
char   level    :レベル
char   xpos,ypos:座標
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

