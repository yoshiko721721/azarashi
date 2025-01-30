#pragma once
#include "../../06_Scene/Scene.h"
#include "../../11_Pause/pause.h"
#include "GameBackGround.h"
#include "GameCamera.h"
#include "GamePointer.h"
#include "GameBlock.h"
#include "../../07_Camera/Camera.h"

class GameScene : public Scene
{
private:
	Object sample;
	GameBackGround backGround;
	//GameCamera     camera;
	GamePointer    pointer;
	GameBlock      block;
	ContactPointVector collision;
	Pause	pause;

public:
	void Init();		//‰Šú‰»
	void Update();		//XV
	void Draw();		//•`‰æ
	void Uninit();		//I—¹
};


extern GameScene* gameScene;