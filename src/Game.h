//�Q�[���S�̂̂��
#pragma once
#include "Map.h"
#include "Character.h"


/*�I�u�W�F�N�g���
�}�b�v��̊�{�����Ȃ��I�u�W�F�N�g�Ɋւ�����
�K�i�C�A�C�e���C㩓�
Object_ID.txt�Q��
*/
struct Object{
	int ID;
	char xpos;
	char ypos;
	int CharGraph;
};
extern Object stair;
//�֐��錾
void Game();		//�Q�[���̎��s
void Init();		//������
void DispMinMap(int CangeShift_X, int CangeShift_Y, int ChangeSize);	//�~�j�}�b�v�\��
void CommandExecution();	//�v���C���[�̈ړ�(�����Ftrue / ���s�Ffalse)
void Disp();		//��ʕ\��
void LoadGraphHandle();//�摜�f�[�^�ǂݍ���
int ConversionPosition(int MapPos, int DispPlayerPos, int ChipSize, bool flag);	//�}�b�v���W�����ʍ��W�ւ̕ϊ�

const unsigned int Red = GetColor(255, 0, 0);	//�v���C���[�̐F
const unsigned int Green = GetColor(0, 255, 0);	//�����̐F
const unsigned int Blue = GetColor(0, 0, 255);	//�ǂ̐F
const unsigned int White = GetColor(255, 255, 255);	//�K�i�̐F

//extern int Floor_WallHandle[2];