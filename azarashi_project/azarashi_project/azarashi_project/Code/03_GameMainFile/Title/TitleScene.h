#pragma once
#include "../../06_Scene/Scene.h"
#include"TitleBackGround.h"

class TitleScene : public Scene
{
private:
	Object sample;
	TitleBackGround backGround;

public:
	void Init();		//初期化
	void Update();		//更新
	void Draw();		//描画
	void Uninit();		//終了

};

extern TitleScene* titleScene ;