#include "Game.h"

//宣言
MapData map;//マップ
MapData map_copy;	//マップのコピー
Character player;	//プレイヤー
Object stair;		//ID 0:階段

void Game(){
	clsDx(); //テスト用
	LoadGraphHandle();
	MapDef def;
	map.MapGenerator1(def);
	map.loadGraph(STAGE1_GRAPH);
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
		player.setID(1);
		XY playerpos(GetRand(map.getMapSize() - 1), GetRand(map.getMapSize() - 1));
		player.setPosition(playerpos);
		if (map.getData(player.getPosition()) == ROOM){
			map_copy.setData(player.getPosition(), CHAR1);
			break;
		}
	}
	//階段をどこかのROOMのどこかに配置(playerと重ならない)
	while (1){
		stair.setID(0);
		char xpos = GetRand(map.getMapSize() - 1);
		char ypos = GetRand(map.getMapSize() - 1);
		if (map.getData(xpos, ypos) == ROOM && map_copy.getData(xpos, ypos) != CHAR1){
			stair.setPosition(XY(xpos, ypos));
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
				//壁なら青を表示v    
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
	int x = WindowSize_X - (shift_X + map.getMapSize()*ChipSize) + stair.getX()*ChipSize;
	int y = shift_Y + stair.getY()*ChipSize;
	DrawBox(x, y, x + ChipSize, y + ChipSize, White, TRUE);
	//プレイヤーを赤で表示
	x = WindowSize_X - (shift_X + map.getMapSize()*ChipSize) + player.getX()*ChipSize;
	y = shift_Y + player.getY()*ChipSize;
	DrawBox(x,y,x + ChipSize,y + ChipSize, Red, TRUE);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);	//透過設定をもとに戻す
}

void CommandExecution()
{
	char KeyState = GetInputChar(TRUE);
	
	switch (KeyState){
	//移動
	case CTRL_CODE_LEFT:
		if (map_copy.getData(player.getX()-1, player.getY()) != WALL){
			map_copy.setData(player.getX()-1, player.getY(),CHAR1);
			map_copy.setData(player.getPosition(), map.getData(player.getPosition()));
			player.move(XY(-1, 0));
		}
		break;
	
	case CTRL_CODE_RIGHT:
		if (map_copy.getData(player.getX()+1, player.getY()) != WALL){
			map_copy.setData(player.getX()+1, player.getY(), CHAR1);
			map_copy.setData(player.getPosition(), map.getData(player.getPosition()));
			player.move(XY(1, 0));
		}
		break;
	case CTRL_CODE_UP:
		if (map_copy.getData(player.getX(), player.getY()-1) != WALL) {
			map_copy.setData(player.getX(), player.getY()-1, CHAR1);
			map_copy.setData(player.getPosition(), map.getData(player.getPosition()));
			player.move(XY(0, -1));
		}
		break;
	case CTRL_CODE_DOWN:
		if (map_copy.getData(player.getX(), player.getY()+1) != WALL) {
			map_copy.setData(player.getX(), player.getY()+1, CHAR1);
			map_copy.setData(player.getPosition(), map.getData(player.getPosition()));
			player.move(XY(0, 1));
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
			マップ		   ＞ MapData mapをもとに描画
キャラクター・オブジェクト ＞ それぞれの持つ座標をもとに描画
マップ＞オブジェクト＞キャラクターの順番に描画
プレイヤーが常に画面上の指定した位置に描画される
int player_X,player_Yを変更することでプレイヤーの描画位置を変更可
*/
void Disp() {
	//マップ描画
	map.MapDisp(player.getPosition());
	//プレイヤー描画
	int player_X = WindowSize_X / 2 - MAPCHIPSIZE / 2;//プレイヤーを描画する座標(全ての基準点)
	int player_Y = WindowSize_Y / 2 - MAPCHIPSIZE * 2;
	player.disp(XY(player_X, player_Y));
	//階段描画
	int x = ConversionPosition(stair.getX(), player_X, MAPCHIPSIZE, true);
	int y = ConversionPosition(stair.getY(), player_Y, MAPCHIPSIZE, false);
	stair.disp(XY(x, y));
	
	//DrawGraph(player_X, player_Y, player.CharGraph, TRUE);
}
/*void LoadGraphHandle()
*/
void LoadGraphHandle(){
	player.loadGraph(PLAYER_GRAPH);
	stair.loadGraph("Resource/graph/stair.png");
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
		return DispPlayerPos - player.getX()*ChipSize+MapPos*ChipSize;
	}
	else{
		return DispPlayerPos - player.getY()*ChipSize + MapPos*ChipSize+ChipSize;
	}
}