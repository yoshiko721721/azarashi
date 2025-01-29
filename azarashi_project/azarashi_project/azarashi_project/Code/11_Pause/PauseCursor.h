#pragma once
#include "../01_Direct3D/BackGround.h"
#include "../01_Direct3D/Object.h"
#include "../02_Input/input.h"

class PauseCursor :public BackGround
{
private:

public:
	PauseCursor() {}
	~PauseCursor() { Uninit(); }
	void Init();
	void Update(); //XV
};
