#pragma once
#include "../../01_Direct3D/BackGround.h"
#include "../../02_Input/input.h"
#include "../../02_Input/miyoshi_input/ControllerInput.h"
#include <vector> 
class SelectCursorL :public BackGround
{
private:

public:
	SelectCursorL() {}
	~SelectCursorL() { Uninit(); }
	void Init();
	void Update(int); //�X�V
};
