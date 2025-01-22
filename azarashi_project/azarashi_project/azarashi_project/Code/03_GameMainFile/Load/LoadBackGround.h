#pragma once
#include "../../01_Direct3D/Object.h"
#include "../../02_Input/input.h"

class LoadBackGround :public Object
{
private:

public:
	LoadBackGround() {}
	~LoadBackGround() { Uninit(); }
	void Init();
	void Update(); //çXêV
};