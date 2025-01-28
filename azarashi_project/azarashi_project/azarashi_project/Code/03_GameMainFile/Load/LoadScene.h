#pragma once
#include "../../06_Scene/Scene.h"
#include "LoadBackGround.h"
#include "../Title/TitleBackGroundPAB.h"

class LoadScene : public Scene
{
private:
	LoadBackGround backGround;
	TitleBackGroundPAB backGroundpab;
public:
	LoadScene() {};
	~LoadScene() {  }
	void Init();		//初期化
	void Update();		//更新
	void Draw();		//描画
	void Uninit();		//終了
};

extern LoadScene* loadScene;
