#pragma once
#include "../../01_Direct3D/Object.h"
#include "../../02_Input/input.h"

class SelectBackGround :public Object
{
private:

public:
	SelectBackGround() {}
	~SelectBackGround() { Uninit(); }
	void Init();
	void Update(); //çXêV
};
