#pragma once
#include "Object.h"
#include "input.h"
#include "GameBlock.h"

struct Circle
{
	//float x, y; // 位置
	float radius; // 半径
	float velocityX; // 垂直方向の速度
	float velocityY; // 垂直方向の速度
};

class GamePointer :public Object
{
public:
	GamePointer() {}
	~GamePointer() { Uninit(); }
	void Init();  //初期化
	void Update();//更新
private:
	Input input;
	Circle circle = { 50.0f, 0.0f , 0.0f};
	const float gravity = -0.4f;   // 重力の力
};

