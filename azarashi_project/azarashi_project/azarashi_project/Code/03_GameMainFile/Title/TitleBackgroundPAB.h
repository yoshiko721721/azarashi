#pragma once
#include "../../01_Direct3D/Object.h"
#include "../../02_Input/input.h"

class TitleBackGroundPAB :public Object
{
private:

public:
	TitleBackGroundPAB() {}
	~TitleBackGroundPAB() { Uninit(); }
	void Init();
	void Update(); //�X�V
};
