#pragma once
#include "../../01_Direct3D/Object.h"
#include "../../02_Input/input.h"

class TitleLogo :public Object
{
private:

public:
	TitleLogo() {}
	~TitleLogo() { Uninit(); }
	void Init();
	void Update(); //çXêV
};

