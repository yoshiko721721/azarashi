#pragma once
#include "../../01_Direct3D/Object.h"
#include "../../02_Input/input.h"

class GameBackGround : public Object
{
private:
	Input input;
public:
	GameBackGround() {}
	~GameBackGround() { Uninit(); }
	void Init();  //‰Šú‰»
	void Update();//XV

};
