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
	void Init();		//初期化
	void Update();		//更新
	void Draw();		//描画
	void Uninit();		//終了
};


extern GameScene* gameScene;