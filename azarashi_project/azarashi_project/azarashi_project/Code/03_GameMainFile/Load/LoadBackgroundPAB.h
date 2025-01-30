#pragma once
#include "../../01_Direct3D/Object.h"
#include "../../02_Input/input.h"

class LoadBackGroundPAB :public Object
{
private:

public:
	LoadBackGroundPAB() {}
	~LoadBackGroundPAB() { Uninit(); }
	void Init();
	void Update(); //çXêV
};
