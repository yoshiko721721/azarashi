#pragma once
#include "Object.h"
#include "input.h"

	const float groundY = -200.0f; // 地面のY座標
	const float groundX = 0.0f; // 地面のY座標

class GameBlock :public Object
{
public:
	GameBlock() {}
	~GameBlock() { Uninit(); }
	void Init();  //初期化
	void Update();//更新
private:
	Input input;
	float angle = 0.0f;
};

