#pragma once
#include "../06_Scene/Scene.h"


class GameScene : public Scene
{
private:
	Object sample;

public:
	void Init();		//������
	void Update();		//�X�V
	void Draw();		//�`��
	void Uninit();		//�I��
};


extern GameScene* gameScene;