#pragma once
#include "Object.h"
#include "input.h"
class GameBackground :public Object
{
public:
	GameBackground() {}
	~GameBackground() { Uninit(); }
	void Init();  //������
	void Update();//�X�V
private:
	Input input;

};
