#pragma once
#include "../../01_Direct3D/BackGround.h"
#include "../../01_Direct3D/Object.h"
#include "../../02_Input/input.h"

class StageExplanation :public BackGround
{
private:

public:
	StageExplanation() {}
	~StageExplanation() { Uninit(); }
	void Init();
	void Update(); //çXêV
};

