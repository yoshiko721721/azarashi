#pragma once
#include "../../01_Direct3D/BackGround.h"
#include "../../01_Direct3D/Object.h"
#include "../../02_Input/input.h"

class PauseBackGround :public BackGround
{
private:

public:
	PauseBackGround() {}
	~PauseBackGround() { Uninit(); }
	void Init();
	void Update(); //çXêV
};


