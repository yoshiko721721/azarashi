#pragma once
#include "Object.h"
#include "input.h"
#include "GameBlock.h"

struct Circle
{
	//float x, y; // �ʒu
	float radius; // ���a
	float velocityX; // ���������̑��x
	float velocityY; // ���������̑��x
};

class GamePointer :public Object
{
public:
	GamePointer() {}
	~GamePointer() { Uninit(); }
	void Init();  //������
	void Update();//�X�V
private:
	Input input;
	Circle circle = { 50.0f, 0.0f , 0.0f};
	const float gravity = -0.4f;   // �d�̗͂�
};

