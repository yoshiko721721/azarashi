#pragma once
#include "../../06_Scene/Scene.h"
#include "TitleBackGround.h"
#include "TitleBackGroundPAB.h"
#include "../../09_Sound/sound.h"
#include "TitleLogo.h"
#include "../../13_Effect/FadeEffect.h"
//#include "You_Fade/Fade.h"
//#include "../You_Load/Load.h"

class TitleScene : public Scene
{
private:
	//Object sample;
	TitleBackGround backGround;  //�^�C�g���w�i
	TitleBackGroundPAB backGroundpab;//�^�C�g���̃{�^���w��
	TitleLogo titleLogo;//�^�C�g�����S
	FadeEffect fade;
	bool isFading = true;//�t�F�[�h���I����Ă��邩
	//Fade fade;
	//Load load;

public:
	TitleScene(){};
	~TitleScene() {  }
	void Init();		//������
	void Update();		//�X�V
	void Draw();		//�`��
	void Uninit();		//�I��
};

extern TitleScene* titleScene ;