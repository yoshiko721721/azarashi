#pragma once
#include "../../01_Direct3D/BackGround.h"
#include "../../01_Direct3D/Object.h"
#include "../../02_Input/input.h"

class TitleBackGround :public BackGround
{
private:

public:
	TitleBackGround() {}
	~TitleBackGround() { Uninit(); }
	void Init();
	void Update(); //�X�V
};
