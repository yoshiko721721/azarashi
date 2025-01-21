#pragma once
#include "../../06_Scene/Scene.h"

class TestScene_You : public Scene
{
private:

public:
	TestScene_You() {};
	~TestScene_You() {  }
	void Init();		//‰Šú‰»
	void Update();		//XV
	void Draw();		//•`‰æ
	void Uninit();		//I—¹
};

extern TestScene_You* testScene_You;
