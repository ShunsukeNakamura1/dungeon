#pragma once
#include <DxLib.h>
#include "GameOptions.h"

#define MAPCHIPSIZE 32

const char SECT_NUM_MAX = 5; //���̍ő吔

const char ROOM_SIZE_MAX = 15; //�����̍ő�T�C�Y

const char GAP_SIZE = 3; //��擯�m�̌��Ԃ̍ő�T�C�Y

const char MAP_SIZE_MAX = SECT_NUM_MAX * ROOM_SIZE_MAX+ (SECT_NUM_MAX - 1) * GAP_SIZE; //�ő�}�b�v�T�C�Y



//�}�b�v�̃}�X�̎��
//WALL:��(�ړ��s��)
//ROOM:����(�ړ���)
//ROAD:�ʘH(�ړ���)
enum Chip {
	WALL,
	ROOM,
	ROAD,
	CHAR1
};

struct MapDef {
	char ROOM_SIZE = 10;
	char SECT_NUM = 3;
	char ROOM_NUM_MIN = 4;
	char ROOM_NUM_MAX = 7;
};
struct Link {
	bool flag[4];
};
enum {
	UP,
	DOWN,
	LEFT,
	RIGHT
};

//����(�����)���
struct RoomData {
	char data[ROOM_SIZE_MAX][ROOM_SIZE_MAX];
	char x1, y1, x2, y2;
};

struct MapData {
private:
	char data[MAP_SIZE_MAX][MAP_SIZE_MAX];
	MapDef def;
	char MAP_SIZE;
	int Floor_WallHandle[2]; //���ƕǂ̉摜

	
	//�A���S���Y��1
	void MapDefSet(MapDef);
	RoomData RoomMaker();
	void MakeRectRoom(RoomData*);
	void MakeDigRoom(RoomData*);
	void MakeShiftRoom(RoomData*);
	void RoomSet(char, char, RoomData);
	int CheckLink(int, int, int, Link[][SECT_NUM_MAX], bool[][SECT_NUM_MAX], bool[][SECT_NUM_MAX]);
	//�A���S���Y��2

public:
	MapData();
	MapData(std::string filename);
	void MapGenerator1(MapDef);	//�����ɕ������č��A���S���Y��
	void loadGraph(std::string filename);
	void MapDisp(XY playerPos);	//�}�b�v�\��
	void setData(int, int, char);
	void setData(XY position, char d);
	char getData(int, int);
	char getData(XY position);
	char getMapSize();
};