#pragma once
#include "Object.h"
#include "input.h"
class GameBackground :public Object
{
public:
	GameBackground() {}
	~GameBackground() { Uninit(); }
	void Init();  //‰Šú‰»
	void Update();//XV
private:
	Input input;

};
