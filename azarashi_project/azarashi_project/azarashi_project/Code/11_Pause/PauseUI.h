#pragma once
#include "../01_Direct3D/BackGround.h"
#include "../01_Direct3D/Object.h"
#include "../02_Input/input.h"

class PauseUI :public BackGround
{
private:

public:
	PauseUI() {}
	~PauseUI() { Uninit(); }
	void Init();
	void Update(); //�X�V
};
