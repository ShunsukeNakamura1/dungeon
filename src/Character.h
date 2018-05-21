#pragma once
#include <DxLib.h>
#include "GameOptions.h"

/*キャラクター情報
char[] name     :名前
char   level    :レベル
char   xpos,ypos:座標
*/
struct Character {
private:
	char name[32];
	char ID;
	char level;
	XY position;
	int CharGraph;
	int exp;
public:
	void setID(char ID);
	void setLevel(char level);
	void setPosition(XY position);
	void loadGraph(std::string filename);
	void setExp(int exp);

	char getID();
	char getLevel();
	XY getPosition();
	char getX();
	char getY();

	void disp(XY position);
	void move(XY value);
};
extern Character player;

