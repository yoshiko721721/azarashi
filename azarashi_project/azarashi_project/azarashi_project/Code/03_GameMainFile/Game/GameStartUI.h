#pragma once
#include "../../01_Direct3D/BackGround.h"
//#include "../../01_Direct3D/Object.h"
#include "../../02_Input/input.h"
#include "../../02_Input/miyoshi_input/ControllerInput.h"

class GameStartUI : public BackGround

{
private:

public:
	GameStartUI() {}
	~GameStartUI() { Uninit(); }
	void Init();  //‰Šú‰»
	void Update();//XV

};

