#pragma once
#include <DxLib.h>

const char SECT_NUM_MAX = 5; //���̍ő吔

const char ROOM_SIZE_MAX = 15; //�����̍ő�T�C�Y

const char GAP_SIZE = 3; //��擯�m�̌��Ԃ̍ő�T�C�Y

const char MAP_SIZE_MAX = SECT_NUM_MAX * ROOM_SIZE_MAX
+ (SECT_NUM_MAX - 1) * GAP_SIZE; //�ő�}�b�v�T�C�Y

								 //�}�b�v�̃}�X�̎��
								 //WALL:��(�ړ��s��)
								 //ROOM:����(�ړ���)
								 //ROAD:�ʘH(�ړ���)
enum CHIP {
	WALL,
	ROOM,
	ROAD,
	CHAR1
};

struct MAPDEF {
	char ROOM_SIZE = 10;
	char SECT_NUM = 3;
	char ROOM_NUM_MIN = 4;
	char ROOM_NUM_MAX = 7;
};
struct LINK {
	bool flag[4];
};
enum {
	UP,
	DOWN,
	LEFT,
	RIGHT
};

//����(�����)���
struct ROOMDATA {
	char data[ROOM_SIZE_MAX][ROOM_SIZE_MAX];
	char x1, y1, x2, y2;
};

class MAPDATA {
private:
	char data[MAP_SIZE_MAX][MAP_SIZE_MAX];
	MAPDEF def;
	char MAP_SIZE;

	//�A���S���Y��1
	void MapDefSet(MAPDEF);
	ROOMDATA RoomMaker();
	void MakeRectRoom(ROOMDATA*);
	void MakeDigRoom(ROOMDATA*);
	void MakeShiftRoom(ROOMDATA*);
	void RoomSet(char, char, ROOMDATA);
	int CheckLink(int, int, int, LINK[][SECT_NUM_MAX], bool[][SECT_NUM_MAX], bool[][SECT_NUM_MAX]);
	//�A���S���Y��2

public:
	void MapGenerator1(MAPDEF);	//�����ɕ������č��A���S���Y��

	void MapDisp();	//�}�b�v�\��
	void setData(int, int, char);
	char getData(int, int);
	char getMapSize();
};