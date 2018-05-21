#pragma once
#include <DxLib.h>
#include "GameOptions.h"

#define MAPCHIPSIZE 32

const char SECT_NUM_MAX = 5; //区画の最大数

const char ROOM_SIZE_MAX = 15; //部屋の最大サイズ

const char GAP_SIZE = 3; //区画同士の隙間の最大サイズ

const char MAP_SIZE_MAX = SECT_NUM_MAX * ROOM_SIZE_MAX+ (SECT_NUM_MAX - 1) * GAP_SIZE; //最大マップサイズ



//マップのマスの種類
//WALL:壁(移動不可)
//ROOM:部屋(移動可)
//ROAD:通路(移動可)
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

//部屋(小区画)情報
struct RoomData {
	char data[ROOM_SIZE_MAX][ROOM_SIZE_MAX];
	char x1, y1, x2, y2;
};

struct MapData {
private:
	char data[MAP_SIZE_MAX][MAP_SIZE_MAX];
	MapDef def;
	char MAP_SIZE;
	int Floor_WallHandle[2]; //床と壁の画像

	
	//アルゴリズム1
	void MapDefSet(MapDef);
	RoomData RoomMaker();
	void MakeRectRoom(RoomData*);
	void MakeDigRoom(RoomData*);
	void MakeShiftRoom(RoomData*);
	void RoomSet(char, char, RoomData);
	int CheckLink(int, int, int, Link[][SECT_NUM_MAX], bool[][SECT_NUM_MAX], bool[][SECT_NUM_MAX]);
	//アルゴリズム2

public:
	MapData();
	MapData(std::string filename);
	void MapGenerator1(MapDef);	//小区画に分割して削るアルゴリズム
	void loadGraph(std::string filename);
	void MapDisp(XY playerPos);	//マップ表示
	void setData(int, int, char);
	void setData(XY position, char d);
	char getData(int, int);
	char getData(XY position);
	char getMapSize();
};