#pragma once
#include "../../06_Scene/Scene.h"
#include"TitleBackGround.h"

class TitleScene : public Scene
{
private:
	Object sample;
	TitleBackGround backGround;

public:
	void Init();		//������
	void Update();		//�X�V
	void Draw();		//�`��
	void Uninit();		//�I��

};

extern TitleScene* titleScene ;