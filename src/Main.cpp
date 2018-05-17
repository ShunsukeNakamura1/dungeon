#include "Game.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){
	
	ChangeWindowMode(TRUE);
	SetGraphMode(WindowSize_X, WindowSize_Y, 32);
	if (DxLib_Init() == -1){
		return -1;    // エラーが起きたら直ちに終了
	}
	SetDrawScreen(DX_SCREEN_BACK);
	Game();
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0) {
		
		
		ScreenFlip();
	}

	DxLib_End();        // ＤＸライブラリ使用の終了処理

	return 0;        // ソフトの終了
}