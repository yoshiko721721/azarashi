#pragma once
#include"../../01_Direct3D/direct3d.h"
#include "../../01_Direct3D/Object.h"
#include "../../05_WICTextureLoader/WICTextureLoader.h" // �e�N�X�`���ǂݍ��݃��C�u����
#include "../../02_Input/input.h"
#include "random"

class Load :public Object
{
private:
	Input input;		//�C���v�b�g

	float loadCounter;		//���[�h�J�E���^�[
	bool isLoading = false;	//���[�f�B���O�t���O
	int scene = 0;		//�V�[���ϐ��A�ꉞ�ݒ肵�܂����A���scene�̂�Ɠ������܂�
	int nextscene = 0;	//���ɓǂݍ��ރV�[���̒l
public:
	//Load ( ) {}
	//~Load ( ) { Uninit ( ); }

	void Init ( );
	void Update ( );//�X�V

};
