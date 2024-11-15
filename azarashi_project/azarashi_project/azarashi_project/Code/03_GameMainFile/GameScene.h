#pragma once
#include "../06_Scene/Scene.h"


class GameScene : public Scene
{
private:
	Object sample;

public:
	void Init();		//‰Šú‰»
	void Update();		//XV
	void Draw();		//•`‰æ
	void Uninit();		//I—¹
};


extern GameScene* gameScene;