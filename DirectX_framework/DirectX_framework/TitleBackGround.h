#pragma once
#include "Object.h"
#include "input.h"

class TitleBackground :public Object
{
public:
	TitleBackground() {}
	~TitleBackground() { Uninit(); }
	void Init();  //初期化
	void Update();//更新
private:
	Input input;
};
