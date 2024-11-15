#pragma once
#include "../../06_Scene/Scene.h"
#include"TitleBackGround.h"

class TitleScene : public Scene
{
private:
	Object sample;
	TitleBackGround backGround;

public:
	void Init();		//‰Šú‰»
	void Update();		//XV
	void Draw();		//•`‰æ
	void Uninit();		//I—¹

};

extern TitleScene* titleScene ;