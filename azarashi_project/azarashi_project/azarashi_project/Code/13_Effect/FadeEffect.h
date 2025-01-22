#pragma once
#include "../01_Direct3D/direct3d.h"
#include "../01_Direct3D/Object.h"
#include "../05_WICTextureLoader/WICTextureLoader.h" // �e�N�X�`���ǂݍ��݃��C�u����

enum Mode			//�t�F�C�h���[�h���
{
	FADEIN ,
	FADEOUT ,
};

class FadeEffect :public Object
{
private:

	Mode fademode;		//�t�F�C�h���[�h

	float fadeInCounter;		//�t�F�C�h�E�C���J�E���g
	float fadeOutCounter;		//�t�F�C�h�E�A�E�g�J�E���g
	float a;				//�����x�ϐ�
	bool isFading;
public:
	/*FadeEffect(Mode Type)
	{
		fademode = Type	
	}*/
	//~Fade ( ) { Uninit ( ); }

	void Init ( );
	bool Update (float);//�X�V
	void SetMode(Mode changeMode)
	{
		fademode = changeMode;
	}
	void SetisFading(bool changeisFade)
	{
		isFading = changeisFade;
	}

	Mode GetMode()
	{
		return fademode;
	}
};

