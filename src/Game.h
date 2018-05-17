//ゲーム全体のやつ
#pragma once
#include "Map.h"
#include "Character.h"

//ウインドウサイズ
const int WindowSize_X = 800;
const int WindowSize_Y = 600;


/*オブジェクト情報
マップ上の基本動かないオブジェクトに関する情報
階段，アイテム，罠等
OBJECT_ID.txt参照
*/
struct OBJECT{
	int ID;
	char xpos;
	char ypos;
	int CharGraph;
};
extern OBJECT stair;
//関数宣言
void Game();		//ゲームの実行
void Init();		//初期化
void DispMinMap(int CangeShift_X, int CangeShift_Y, int ChangeSize);	//ミニマップ表示
void CommandExecution();	//プレイヤーの移動(成功：true / 失敗：false)
void Disp();		//画面表示
void LoadGraphHandle();//画像データ読み込み
int ConversionPosition(int MapPos, int DispPlayerPos, int ChipSize, bool flag);	//マップ座標から画面座標への変換

const unsigned int Red = GetColor(255, 0, 0);	//プレイヤーの色
const unsigned int Green = GetColor(0, 255, 0);	//部屋の色
const unsigned int Blue = GetColor(0, 0, 255);	//壁の色
const unsigned int White = GetColor(255, 255, 255);	//階段の色

extern int Floor_WallHandle[2];