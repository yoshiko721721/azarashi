#pragma once
#include "../../01_Direct3D/Object.h"
#include "../../02_Input/input.h"
#include "../../03_GameMainFile/RigidBody.h"
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
	RigidBody body;

	GamePointer() {}
	~GamePointer() { Uninit(); }
	void Init();  //������
	void Update();//�X�V


	//���a�̃Q�b�^�[
	float GetCircleRadius();
	float GetFrictionResistance();



	void  RotateTexture(const float sub);	//�摜�𒚓x�悭��]
	//float GetCirclePosX();
	//float GetCirclePosY();

private:
	Circle circle;
	const float frictionResistance = 0.5;		// ���C�W��
	//const float gravity = -0.4f;				// �d�̗͂�
};

