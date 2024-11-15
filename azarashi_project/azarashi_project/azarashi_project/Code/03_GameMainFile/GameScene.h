#pragma once
#include "../06_Scene/Scene.h"


class GameScene : public Scene
{
private:
	Object sample;

public:
	void Init();		//初期化
	void Update();		//更新
	void Draw();		//描画
	void Uninit();		//終了
};


extern GameScene* gameScene;