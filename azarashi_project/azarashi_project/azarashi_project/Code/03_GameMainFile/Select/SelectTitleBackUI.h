#pragma once
#include "../../01_Direct3D/Object.h"
#include "../../02_Input/input.h"
#include "../../02_Input/miyoshi_input/ControllerInput.h"
#include <vector> 
class TitleBackUI :public Object
{
private:

public:
	TitleBackUI() {}
	~TitleBackUI() { Uninit(); }
	void Init();
	void Update(int); //çXêV
};
