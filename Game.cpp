#include "Game.h"

//�錾
MAPDATA map;		//�}�b�v
MAPDATA map_copy;	//�}�b�v�̃R�s�[
CHARACTER player;	//�v���C���[
OBJECT stair;		//ID 0:�K�i
int Floor_WallHandle[2];
void Game(){
	clsDx(); //�e�X�g�p
	LoadGraphHandle();
	MAPDEF def;
	//def.ROOM_SIZE = 15;
	//def.SECT_NUM = 4;
	map.MapGenerator1(def);
	map_copy = map; //�}�b�v�̃R�s�[
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
�������p�֐�
�v���C���[�C�K�i�̈ʒu��������
*/
void Init(){
	//�v���C���[���ǂ�����ROOM�̂ǂ����ɔz�u
	while (1){
		player.ID = 1;
		player.xpos = GetRand(map.getMapSize()-1);
		player.ypos = GetRand(map.getMapSize()-1);
		if (map.getData(player.xpos, player.ypos) == ROOM){
			map_copy.setData(player.xpos, player.ypos, CHAR1);
			break;
		}
	}
	//�K�i���ǂ�����ROOM�̂ǂ����ɔz�u(player�Əd�Ȃ�Ȃ�)
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
�~�j�}�b�v�̕\��
CangeShift_X   :��ʉE�ォ���x�������ւ̃V�t�g�ʂ̕ύX�l[pixel]
CangeShift_Y   :��ʉE�ォ���y�������ւ̃V�t�g�ʂ̕ύX�l[pixel]
ChangeSize:�~�j�}�b�v1�}�X(�`�b�v)������̑傫���̕ύX�l[pixel]
*/
void DispMinMap(int CangeShift_X, int CangeShift_Y, int ChangeSize)
{
	static int shift_X = 50;	//��ʉE�ォ���x�������ւ̃V�t�g��[pixel]
	static int shift_Y = 50;	//��ʉE�ォ���y�������ւ̃V�t�g��[pixel]
	static int ChipSize = 5;	//�~�j�}�b�v1�}�X(�`�b�v)������̑傫��[pixel]
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
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);	//���ߏ���
	for (int i=0; i < map.getMapSize(); i++){
		for (int j = 0; j < map.getMapSize(); j++){
			//�`�ʊJ�n�ʒu(����)�ƏI���ʒu(�E��)
			int x = WindowSize_X - (shift_X + mapsize) + i*ChipSize;
			int x2 = WindowSize_X - (shift_X + mapsize) + (i + 1)*ChipSize;
			int y = shift_Y + j*ChipSize;
			int y2 = shift_Y + (j + 1)*ChipSize;
			switch (map.getData(i, j)){
				//�ǂȂ��\��
				case WALL:
					DrawBox(x,y,x + ChipSize,y + ChipSize, Blue, TRUE);
					break;
				//�������ʘH�Ȃ�΂�\��
				case ROOM:
				case ROAD:
					DrawBox(x,y,x + ChipSize,y + ChipSize, Green, TRUE);
					break;
			}
		}
	}
	
	//�K�i�𔒂ŕ\��
	int x = WindowSize_X - (shift_X + map.getMapSize()*ChipSize) + stair.xpos*ChipSize;
	int y = shift_Y + stair.ypos*ChipSize;
	DrawBox(x, y, x + ChipSize, y + ChipSize, White, TRUE);
	//�v���C���[��Ԃŕ\��
	x = WindowSize_X - (shift_X + map.getMapSize()*ChipSize) + player.xpos*ChipSize;
	y = shift_Y + player.ypos*ChipSize;
	DrawBox(x,y,x + ChipSize,y + ChipSize, Red, TRUE);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);	//���ߐݒ�����Ƃɖ߂�
}

void CommandExecution()
{
	char KeyState = GetInputChar(TRUE);
	
	switch (KeyState){
	//�ړ�
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
	//�~�j�}�b�v�T�C�Y�ύX
	case 'z':
		DispMinMap(0, 0, 2);
		break;
	case 'x':
		DispMinMap(0, 0, -2);
		break;
	//�~�j�}�b�v�ʒu�ύX
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
��ʕ\��
			�}�b�v		   �� MAPDATA map�����Ƃɕ`��
�L�����N�^�[�E�I�u�W�F�N�g �� ���ꂼ��̎����W�����Ƃɕ`��
�}�b�v���I�u�W�F�N�g���L�����N�^�[�̏��Ԃɕ`��
�v���C���[����ɉ�ʏ�̎w�肵���ʒu�ɕ`�悳���
int player_X,player_Y��ύX���邱�ƂŃv���C���[�̕`��ʒu��ύX��
*/
void Disp() {
	
	int ChipSize = 32;
	//�v���C���[��`�悷����W(�S�Ă̊�_)
	int player_X = WindowSize_X / 2 - ChipSize / 2;
	int player_Y = WindowSize_Y / 2 - ChipSize * 2;
	
	//�}�b�v�`��̊J�n�_
	int point_X = player_X -player.xpos*ChipSize;
	int point_Y = player_Y -player.ypos*ChipSize+32;

	for (int i = 0; i < map.getMapSize(); i++){
		for (int j = 0; j < map.getMapSize(); j++) {
			//�Ǖ`��
			if (map.getData(j, i) == WALL){
				DrawGraph(j*ChipSize + point_X,i*ChipSize + point_Y,Floor_WallHandle[1],TRUE);
			}
			//���`��
			else{
				DrawGraph(j*ChipSize + point_X, i*ChipSize + point_Y, Floor_WallHandle[0], TRUE);
			}
		}
	}
	//�K�i�`��
	int x = ConversionPosition(stair.xpos, player_X, ChipSize, true);
	int y = ConversionPosition(stair.ypos, player_Y, ChipSize, false);
	DrawGraph(x, y, stair.CharGraph, TRUE);
	//�v���C���[�`��
	DrawGraph(player_X, player_Y, player.CharGraph, TRUE);
}
/*void LoadGraphHandle()
�X�e�[�W���ƂɎg���摜�f�[�^�̓ǂݍ���
*/
void LoadGraphHandle(){
	player.CharGraph = LoadGraph("Resource/graph/player.png");
	stair.CharGraph = LoadGraph("Resource/graph/stair.png");
	LoadDivGraph("Resource/graph/floor_wall.png", 2, 2, 1, 32, 32, Floor_WallHandle);
}

/*int ConversionPosition(int MapPos, int DispPlayerPos, int ChipSize, bool flag)
�}�b�v�ɂ�������W����ʕ\���ɂ�������W�ɕϊ�����֐�
int MapPos			:�}�b�v�ɂ�������W
int DispPlayerPos	:��ʕ\���ɂ�����v���C���[�̍��W
int ChipSize		:1�}�X�̃T�C�Y
bool flag			:x����y�����̎���	true:x��    false:y��
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