#pragma once
#include "../../06_Scene/Scene.h"
#include "GameBackGround.h"
#include "GameCamera.h"
#include "GamePointer.h"
#include "GameBlock.h"

class GameScene : public Scene
{
private:
	Object sample;
	GameBackGround backGround;
	//GameCamera     camera;
	GamePointer    pointer;
	GameBlock      block;

public:
	void Init();		//������
	void Update();		//�X�V
	void Draw();		//�`��
	void Uninit();		//�I��
};


extern GameScene* gameScene;