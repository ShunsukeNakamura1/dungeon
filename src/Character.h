#pragma once
#include <DxLib.h>
#include "GameOptions.h"

/*�L�����N�^�[���
char[] name     :���O
char   level    :���x��
char   xpos,ypos:���W
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


/*�I�u�W�F�N�g���
�}�b�v��̊�{�����Ȃ��I�u�W�F�N�g�Ɋւ�����
�K�i�C�A�C�e���C㩓�
Object_ID.txt�Q��
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



