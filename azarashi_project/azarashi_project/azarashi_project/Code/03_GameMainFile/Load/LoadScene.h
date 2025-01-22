#pragma once
#include "../../06_Scene/Scene.h"
#include "LoadBackGround.h"

class LoadScene : public Scene
{
private:
	LoadBackGround backGround;
public:
	LoadScene() {};
	~LoadScene() {  }
	void Init();		//‰Šú‰»
	void Update();		//XV
	void Draw();		//•`‰æ
	void Uninit();		//I—¹
};

extern LoadScene* loadScene;
