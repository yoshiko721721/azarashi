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
	void Update(float blockAngle);//�X�V


	float GetCircleRadius();		//���a�̃Q�b�^�[
	float GetFrictionResistance();	//���C��R�̃Q�b�^�[
	
	void  RotateTexture(const float sub);					//�摜�𒚓x�悭��]
	void  CorrectionPos(Object* p_player, Object* p_block);	//���W�̕␳
	//float GetCirclePosX();
	//float GetCirclePosY();

private:
	Circle circle;
	const float frictionResistance = 0.5;		// ���C�W��
	//const float gravity = -0.4f;				// �d�̗͂�
};

