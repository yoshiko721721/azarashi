#pragma once
#include "../../06_Scene/Scene.h"

class TestScene_You : public Scene
{
private:

public:
	TestScene_You() {};
	~TestScene_You() {  }
	void Init();		//初期化
	void Update();		//更新
	void Draw();		//描画
	void Uninit();		//終了
};

extern TestScene_You* testScene_You;
