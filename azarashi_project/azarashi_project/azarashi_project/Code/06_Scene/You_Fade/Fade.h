#pragma once
#include"../../../01_Direct3D/direct3d.h"
#include "../../../01_Direct3D/Object.h"
#include "../../../05_WICTextureLoader/WICTextureLoader.h" // �e�N�X�`���ǂݍ��݃��C�u����

class Fade :public Object
{
private:
	enum Mode			//�t�F�C�h���[�h���
	{
		FadeIn ,
		FadeOut ,
	};

	Mode fademode;		//�t�F�C�h���[�h

	float fadeInCounter;		//�t�F�C�h�E�C���J�E���g
	float fadeOutCounter;		//�t�F�C�h�E�A�E�g�J�E���g

	float a;				//�����x�ϐ�
public:
	//Fade ( ) {}
	//~Fade ( ) { Uninit ( ); }

	void Init ( );
	void Update ( );//�X�V
};

