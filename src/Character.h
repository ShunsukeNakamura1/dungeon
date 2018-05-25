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


/*オブジェクト情報
マップ上の基本動かないオブジェクトに関する情報
階段，アイテム，罠等
Object_ID.txt参照
*/
struct Object {
private:
	int ID;
	XY position;
	int CharGraph;
public:
	void setID(int ID);
	void setPosition(XY position);
	void loadGraph(std::string filename);

	int getID();
	XY getPosition();
	char getX();
	char getY();
	void disp(XY position);
};



