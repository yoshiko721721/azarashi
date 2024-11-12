#pragma once
#include "Object.h"
#include "input.h"

class TitleBackground :public Object
{
public:
	TitleBackground() {}
	~TitleBackground() { Uninit(); }
	void Init();  //‰Šú‰»
	void Update();//XV
private:
	Input input;
};
