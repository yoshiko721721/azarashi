#pragma once
#include "../../01_Direct3D/Object.h"
#include "../../02_Input/input.h"

class GameBackGround : public Object
{
private:

public:
	GameBackGround() {}
	~GameBackGround() { Uninit(); }
	void Init();  //初期化
	void Update();//更新

};
