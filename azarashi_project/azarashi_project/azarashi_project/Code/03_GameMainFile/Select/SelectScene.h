#pragma once
#include "../../06_Scene/Scene.h"

class SelectScene : public Scene
{
private:
	Object sample;
	std::vector<Object*> m_MySceneObjects; // このシーンのオブジェクト

public:
	void Init();		//初期化
	void Update();		//更新
	void Draw();		//描画
	void Uninit();		//終了

};