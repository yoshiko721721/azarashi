#pragma once
#include "Object.h"
#include "input.h"

	const float groundY = -200.0f; // �n�ʂ�Y���W
	const float groundX = 0.0f; // �n�ʂ�Y���W

class GameBlock :public Object
{
public:
	GameBlock() {}
	~GameBlock() { Uninit(); }
	void Init();  //������
	void Update();//�X�V
private:
	Input input;
	float angle = 0.0f;
};

