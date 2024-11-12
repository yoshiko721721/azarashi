#pragma once
#include "camera.h"
#include "input.h"

class GameCamera :public Camera
{
public:
	void Init();
	void Update();
	void Draw();
	void Uninit();
private:
	Input input;
};