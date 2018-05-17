#pragma once
#include <DxLib.h>

const char SECT_NUM_MAX = 5; //区画の最大数

const char ROOM_SIZE_MAX = 15; //部屋の最大サイズ

const char GAP_SIZE = 3; //区画同士の隙間の最大サイズ

const char MAP_SIZE_MAX = SECT_NUM_MAX * ROOM_SIZE_MAX
+ (SECT_NUM_MAX - 1) * GAP_SIZE; //最大マップサイズ

								 //マップのマスの種類
								 //WALL:壁(移動不可)
								 //ROOM:部屋(移動可)
								 //ROAD:通路(移動可)
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

//部屋(小区画)情報
struct ROOMDATA {
	char data[ROOM_SIZE_MAX][ROOM_SIZE_MAX];
	char x1, y1, x2, y2;
};

class MAPDATA {
private:
	char data[MAP_SIZE_MAX][MAP_SIZE_MAX];
	MAPDEF def;
	char MAP_SIZE;

	//アルゴリズム1
	void MapDefSet(MAPDEF);
	ROOMDATA RoomMaker();
	void MakeRectRoom(ROOMDATA*);
	void MakeDigRoom(ROOMDATA*);
	void MakeShiftRoom(ROOMDATA*);
	void RoomSet(char, char, ROOMDATA);
	int CheckLink(int, int, int, LINK[][SECT_NUM_MAX], bool[][SECT_NUM_MAX], bool[][SECT_NUM_MAX]);
	//アルゴリズム2

public:
	void MapGenerator1(MAPDEF);	//小区画に分割して削るアルゴリズム

	void MapDisp();	//マップ表示
	void setData(int, int, char);
	char getData(int, int);
	char getMapSize();
};