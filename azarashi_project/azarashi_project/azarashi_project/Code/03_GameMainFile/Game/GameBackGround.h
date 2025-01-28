#pragma once
#include "../../01_Direct3D/BackGround.h"
#include "../../01_Direct3D/Object.h"
#include "../../02_Input/input.h"

class GameBackGround : public BackGround

{
private:

public:
	GameBackGround() {}
	~GameBackGround() { Uninit(); }
	void Init();  //初期化
	void Update();//更新

};
