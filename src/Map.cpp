#include "Map.h"

MapData::MapData(){}
MapData::MapData(std::string filename) {
	//loadGraph(filename);
	LoadDivGraph(filename.c_str(), 2, 2, 1, MAPCHIPSIZE, MAPCHIPSIZE, Floor_WallHandle);
}

void MapData::MapGenerator1(MapDef MapDef) {
	MapDefSet(MapDef);
	int roomNum = GetRand(def.ROOM_NUM_MAX - def.ROOM_NUM_MIN) + def.ROOM_NUM_MIN; //������

	bool isRoomExist[SECT_NUM_MAX][SECT_NUM_MAX] = {false}; //3*3�ɋ�؂����}�b�v�̂ǂ��ɕ��������݂��邩
	RoomData *roomdata = new RoomData[roomNum];
	for (int i = 0; i < roomNum;) {
		int x = GetRand(def.SECT_NUM - 1);
		int y = GetRand(def.SECT_NUM - 1);
		if (!isRoomExist[x][y]) {
			isRoomExist[x][y] = true;

			roomdata[i] = RoomMaker();
			RoomSet(x, y, roomdata[i]);//�}�b�v�ɕ�����z�u����֐�

			i++;
		}
	}
}

void MapData::MapDefSet(MapDef MapDef) {
	def = MapDef;

	if (def.ROOM_SIZE > ROOM_SIZE_MAX) {
		def.ROOM_SIZE = ROOM_SIZE_MAX;
	}
	if (def.SECT_NUM > SECT_NUM_MAX) {
		def.SECT_NUM = SECT_NUM_MAX;
	}
	if (def.ROOM_NUM_MIN < 2) {
		def.ROOM_NUM_MIN = 2;
	}
	if (def.ROOM_NUM_MAX > def.SECT_NUM*def.SECT_NUM) {
		def.ROOM_NUM_MAX = def.SECT_NUM*def.SECT_NUM;
	}
	MAP_SIZE = def.SECT_NUM * def.ROOM_SIZE + (def.SECT_NUM - 1) * GAP_SIZE; //�ő�}�b�v�T�C�Y
}
RoomData MapData::RoomMaker() {
	RoomData room;
	MakeRectRoom(&room);

	MakeDigRoom(&room);

	MakeShiftRoom(&room);

	return room;
}
void MapData::MakeRectRoom(RoomData *room) {
	room->x1 = 0;
	room->y1 = 0;
	room->x2 = 4 + GetRand(def.ROOM_SIZE - 4);
	room->y2 = 4 + GetRand(def.ROOM_SIZE - 4);

	for (int x = 0; x < def.ROOM_SIZE; x++) {
		for (int y = 0; y < def.ROOM_SIZE; y++) {
			if (x < room->x2 && y < room->y2) {
				room->data[x][y] = ROOM;
			}
			else { room->data[x][y] = WALL; }
		}
	}
}
void MapData::MakeDigRoom(RoomData *room) {
	//��������鐔
	char isDigRoom = GetRand(100);
	if (isDigRoom < 50) { //50�p�[�Z���g�̊m���ŕ�����0���
		isDigRoom = 0;
	}
	else if (isDigRoom < 85) { //40�p�[�Z���g�̊m���ŕ�����1���
		isDigRoom = 1;
	}
	else {					//10�p�[�Z���g�̊m���ŕ�����2���
		isDigRoom = 2;
	}

	const char NOKOSU_MIN = 3; //�Œ�ł��c�������̑傫��
	//���������
	if (isDigRoom >= 1) {
		bool corner1_x = GetRand(1) ? true : false; //0:�� 1:�E
		bool corner1_y = GetRand(1) ? true : false; //0:�� 1:��
		char digSizeX1 = GetRand(room->x2 - NOKOSU_MIN - 1) + 1;
		char digSizeY1 = GetRand(room->y2 - NOKOSU_MIN - 1) + 1;

		char digPosX, digPosY;
		if (corner1_x == 0) { digPosX = 0; }
		else { digPosX = room->x2 - digSizeX1; }
		if (corner1_y == 0) { digPosY = 0; }
		else { digPosY = room->y2 - digSizeY1; }

		for (int y = 0; y < digSizeY1; y++) {
			for (int x = 0; x < digSizeX1; x++) {
				room->data[digPosX + x][digPosY + y] = WALL;
			}
		}

		if (isDigRoom == 2) {

		}
	}
}
void MapData::MakeShiftRoom(RoomData *room) {
	char data[ROOM_SIZE_MAX][ROOM_SIZE_MAX] = { WALL };
	//�����ŕ��������炷��
	int xShift = GetRand(def.ROOM_SIZE - room->x2);
	int yShift = GetRand(def.ROOM_SIZE - room->y2);

	if (xShift == 0 && yShift == 0) { return; }

	for (int y = 0; y < room->y2; y++) {
		for (int x = 0; x < room->x2; x++) {
			data[x + xShift][y + yShift] = room->data[x][y];
		}
	}
	for (int y = 0; y < def.ROOM_SIZE; y++) {
		for (int x = 0; x < def.ROOM_SIZE; x++) {
			room->data[x][y] = data[x][y];
		}
	}

	room->x1 += xShift;
	room->x2 += xShift;
	room->y1 += yShift;
	room->y2 += yShift;
}
void MapData::RoomSet(char RoomNum_X, char RoomNum_Y, RoomData data)
{
	for (int i = 0; i < def.ROOM_SIZE; i++)
	{
		for (int j = 0; j < def.ROOM_SIZE; j++)
		{
			int xPos = RoomNum_X * (def.ROOM_SIZE + GAP_SIZE) + i;
			int yPos = RoomNum_Y * (def.ROOM_SIZE + GAP_SIZE) + j;
			setData(xPos, yPos, data.data[i][j]);
		}
	}
}
int MapData::CheckLink(int, int, int, Link[][SECT_NUM_MAX], bool[][SECT_NUM_MAX], bool[][SECT_NUM_MAX]) {

	return 0;
}


void MapData::loadGraph(std::string filename) {
	LoadDivGraph(filename.c_str(), 2, 2, 1, MAPCHIPSIZE, MAPCHIPSIZE, Floor_WallHandle);
}
void MapData::MapDisp(XY playerPos)
{
	//�v���C���[��`�悷����W(�S�Ă̊�_)
	int player_X = WindowSize_X / 2 - MAPCHIPSIZE / 2;
	int player_Y = WindowSize_Y / 2 - MAPCHIPSIZE * 2;

	//�}�b�v�`��̊J�n�_
	int point_X = player_X - playerPos.x*MAPCHIPSIZE;
	int point_Y = player_Y - playerPos.y*MAPCHIPSIZE + MAPCHIPSIZE;

	for (int i = 0; i < getMapSize(); i++) {
		for (int j = 0; j < getMapSize(); j++) {
			//�Ǖ`��
			if (this->getData(j, i) == WALL) {
				DrawGraph(j*MAPCHIPSIZE + point_X, i*MAPCHIPSIZE + point_Y, Floor_WallHandle[1], TRUE);
			}
			//���`��
			else {
				DrawGraph(j*MAPCHIPSIZE + point_X, i*MAPCHIPSIZE + point_Y, Floor_WallHandle[0], TRUE);
			}
		}
	}
}
void MapData::setData(int x, int y, char d)
{
	data[x][y] = d;
}
char MapData::getData(int x, int y)
{
	return data[x][y];
}
char MapData::getMapSize()
{
	return MAP_SIZE;
}