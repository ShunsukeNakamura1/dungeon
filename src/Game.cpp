#include "Game.h"

//宣言
MAPDATA map;		//マップ
MAPDATA map_copy;	//マップのコピー
CHARACTER player;	//プレイヤー
OBJECT stair;		//ID 0:階段
int Floor_WallHandle[2];
void Game(){
	clsDx(); //テスト用
	LoadGraphHandle();
	MAPDEF def;
	//def.ROOM_SIZE = 15;
	//def.SECT_NUM = 4;
	map.MapGenerator1(def);
	map_copy = map; //マップのコピー
	Init();
	Disp();
	DispMinMap(0,0,0);
	ScreenFlip();
	WaitKey();
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0){
		ClearDrawScreen();
		clsDx();
		if (CheckHitKeyAll()){
			CommandExecution();		
		}
		Disp();
		DispMinMap(0,0,0);
		ScreenFlip();
	}
}

/*void Init()
初期化用関数
プレイヤー，階段の位置を初期化
*/
void Init(){
	//プレイヤーをどこかのROOMのどこかに配置
	while (1){
		player.ID = 1;
		player.xpos = GetRand(map.getMapSize()-1);
		player.ypos = GetRand(map.getMapSize()-1);
		if (map.getData(player.xpos, player.ypos) == ROOM){
			map_copy.setData(player.xpos, player.ypos, CHAR1);
			break;
		}
	}
	//階段をどこかのROOMのどこかに配置(playerと重ならない)
	while (1){
		stair.ID = 0;
		stair.xpos = GetRand(map.getMapSize() - 1);
		stair.ypos = GetRand(map.getMapSize() - 1);
		if (map.getData(stair.xpos, stair.ypos) == ROOM && map_copy.getData(stair.xpos, stair.ypos) != CHAR1){
			break;
		}
	}
}

/*void DispMinMap(int shift_X, int shift_Y, int ChipSize)
ミニマップの表示
CangeShift_X   :画面右上からのx軸方向へのシフト量の変更値[pixel]
CangeShift_Y   :画面右上からのy軸方向へのシフト量の変更値[pixel]
ChangeSize:ミニマップ1マス(チップ)あたりの大きさの変更値[pixel]
*/
void DispMinMap(int CangeShift_X, int CangeShift_Y, int ChangeSize)
{
	static int shift_X = 50;	//画面右上からのx軸方向へのシフト量[pixel]
	static int shift_Y = 50;	//画面右上からのy軸方向へのシフト量[pixel]
	static int ChipSize = 5;	//ミニマップ1マス(チップ)あたりの大きさ[pixel]
	ChipSize += ChangeSize;
	shift_X += CangeShift_X;
	shift_Y += CangeShift_Y;
	int mapsize = ChipSize*map.getMapSize();
	if (ChipSize  > 13 || ChipSize < 0 || mapsize + shift_X > WindowSize_X || mapsize + shift_Y > WindowSize_Y) {
		ChipSize -= ChangeSize;
	}
	if (shift_X<0 || shift_Y<0 || mapsize + shift_X > WindowSize_X || mapsize + shift_Y > WindowSize_Y) {
		shift_X -= CangeShift_X;
		shift_Y -= CangeShift_Y;
	}
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);	//透過処理
	for (int i=0; i < map.getMapSize(); i++){
		for (int j = 0; j < map.getMapSize(); j++){
			//描写開始位置(左上)と終了位置(右下)
			int x = WindowSize_X - (shift_X + mapsize) + i*ChipSize;
			int x2 = WindowSize_X - (shift_X + mapsize) + (i + 1)*ChipSize;
			int y = shift_Y + j*ChipSize;
			int y2 = shift_Y + (j + 1)*ChipSize;
			switch (map.getData(i, j)){
				//壁なら青を表示
				case WALL:
					DrawBox(x,y,x + ChipSize,y + ChipSize, Blue, TRUE);
					break;
				//部屋か通路なら緑を表示
				case ROOM:
				case ROAD:
					DrawBox(x,y,x + ChipSize,y + ChipSize, Green, TRUE);
					break;
			}
		}
	}
	
	//階段を白で表示
	int x = WindowSize_X - (shift_X + map.getMapSize()*ChipSize) + stair.xpos*ChipSize;
	int y = shift_Y + stair.ypos*ChipSize;
	DrawBox(x, y, x + ChipSize, y + ChipSize, White, TRUE);
	//プレイヤーを赤で表示
	x = WindowSize_X - (shift_X + map.getMapSize()*ChipSize) + player.xpos*ChipSize;
	y = shift_Y + player.ypos*ChipSize;
	DrawBox(x,y,x + ChipSize,y + ChipSize, Red, TRUE);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);	//透過設定をもとに戻す
}

void CommandExecution()
{
	char KeyState = GetInputChar(TRUE);
	
	switch (KeyState){
	//移動
	case CTRL_CODE_LEFT:
		if (map_copy.getData(player.xpos-1, player.ypos) != WALL){
			map_copy.setData(player.xpos-1, player.ypos,CHAR1);
			map_copy.setData(player.xpos , player.ypos, map.getData(player.xpos, player.ypos));
			player.xpos--;
		}
		break;
	
	case CTRL_CODE_RIGHT:
		if (map_copy.getData(player.xpos+1, player.ypos) != WALL){
			map_copy.setData(player.xpos+1, player.ypos, CHAR1);
			map_copy.setData(player.xpos, player.ypos, map.getData(player.xpos, player.ypos));
			player.xpos++;
		}
		break;
	case CTRL_CODE_UP:
		if (map_copy.getData(player.xpos, player.ypos-1) != WALL) {
			map_copy.setData(player.xpos, player.ypos-1, CHAR1);
			map_copy.setData(player.xpos, player.ypos, map.getData(player.xpos, player.ypos));
			player.ypos--;
		}
		break;
	case CTRL_CODE_DOWN:
		if (map_copy.getData(player.xpos, player.ypos+1) != WALL) {
			map_copy.setData(player.xpos, player.ypos+1, CHAR1);
			map_copy.setData(player.xpos, player.ypos, map.getData(player.xpos, player.ypos));
			player.ypos++;
		}
		break;
	//ミニマップサイズ変更
	case 'z':
		DispMinMap(0, 0, 2);
		break;
	case 'x':
		DispMinMap(0, 0, -2);
		break;
	//ミニマップ位置変更
	case 'a':
		DispMinMap(20, 0, 0);
		break;
	case 'd':
		DispMinMap(-20, 0, 0);
		break;
	case 'w':
		DispMinMap(0, -20, 0);
		break;
	case 's':
		DispMinMap(0, 20, 0);
		break;
	default:;

	}
}

/*void Disp()
画面表示
			マップ		   ＞ MAPDATA mapをもとに描画
キャラクター・オブジェクト ＞ それぞれの持つ座標をもとに描画
マップ＞オブジェクト＞キャラクターの順番に描画
プレイヤーが常に画面上の指定した位置に描画される
int player_X,player_Yを変更することでプレイヤーの描画位置を変更可
*/
void Disp() {
	
	int ChipSize = 32;
	//プレイヤーを描画する座標(全ての基準点)
	int player_X = WindowSize_X / 2 - ChipSize / 2;
	int player_Y = WindowSize_Y / 2 - ChipSize * 2;
	
	//マップ描画の開始点
	int point_X = player_X -player.xpos*ChipSize;
	int point_Y = player_Y -player.ypos*ChipSize+32;

	for (int i = 0; i < map.getMapSize(); i++){
		for (int j = 0; j < map.getMapSize(); j++) {
			//壁描画
			if (map.getData(j, i) == WALL){
				DrawGraph(j*ChipSize + point_X,i*ChipSize + point_Y,Floor_WallHandle[1],TRUE);
			}
			//床描画
			else{
				DrawGraph(j*ChipSize + point_X, i*ChipSize + point_Y, Floor_WallHandle[0], TRUE);
			}
		}
	}
	//階段描画
	int x = ConversionPosition(stair.xpos, player_X, ChipSize, true);
	int y = ConversionPosition(stair.ypos, player_Y, ChipSize, false);
	DrawGraph(x, y, stair.CharGraph, TRUE);
	//プレイヤー描画
	DrawGraph(player_X, player_Y, player.CharGraph, TRUE);
}
/*void LoadGraphHandle()
ステージごとに使う画像データの読み込み
*/
void LoadGraphHandle(){
	player.CharGraph = LoadGraph("Resource/graph/player.png");
	stair.CharGraph = LoadGraph("Resource/graph/stair.png");
	LoadDivGraph("Resource/graph/floor_wall.png", 2, 2, 1, 32, 32, Floor_WallHandle);
}

/*int ConversionPosition(int MapPos, int DispPlayerPos, int ChipSize, bool flag)
マップにおける座標を画面表示における座標に変換する関数
int MapPos			:マップにおける座標
int DispPlayerPos	:画面表示におけるプレイヤーの座標
int ChipSize		:1マスのサイズ
bool flag			:x軸かy軸かの識別	true:x軸    false:y軸
*/
int ConversionPosition(int MapPos, int DispPlayerPos, int ChipSize, bool flag)
{
	if (flag){
		return DispPlayerPos - player.xpos*ChipSize+MapPos*ChipSize;
	}
	else{
		return DispPlayerPos - player.ypos*ChipSize + MapPos*ChipSize+ChipSize;
	}
}