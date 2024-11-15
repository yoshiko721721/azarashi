#pragma once
#include "../../01_Direct3D/Object.h"
#include "../../02_Input/input.h"
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
	float GetCirclePosX();
	float GetCirclePosY();
private:
	Input input;
	Circle circle = { 50.0f, 0.0f , 0.0f};
	const float gravity = -0.4f;   // �d�̗͂�
};

