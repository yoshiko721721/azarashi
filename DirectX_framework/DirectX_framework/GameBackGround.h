#pragma once
#include "Object.h"
#include "input.h"
class GameBackground :public Object
{
public:
	GameBackground() {}
	~GameBackground() { Uninit(); }
	void Init();  //初期化
	void Update();//更新
private:
	Input input;

};
