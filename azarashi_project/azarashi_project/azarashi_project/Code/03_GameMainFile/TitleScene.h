#pragma once
#include "../06_Scene/Scene.h"


class TitleScene : public Scene
{
private:
	Object sample;

public:
	void Init();		//������
	void Update();		//�X�V
	void Draw();		//�`��
	void Uninit();		//�I��

};

extern TitleScene* titleScene ;