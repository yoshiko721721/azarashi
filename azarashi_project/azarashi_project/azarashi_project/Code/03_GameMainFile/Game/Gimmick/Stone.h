#pragma once
#include "../../../01_Direct3D/Object.h"
#include "../../../02_Input/input.h"
#include "../../../03_GameMainFile/RigidBody.h"
#include"../../../08_Collider/Base_collision.h"
#include "../GameBlock.h"

class Stone :public Object
{
public:

	Stone() {};
	Stone(float posX, float posY, float sizeX, float sizeY) : Object(posX, posY, sizeX, sizeY) {};
	~Stone() { Uninit(); };
	void Init();  //������
	void Update();//�X�V


	float GetCircleRadius();		//���a�̃Q�b�^�[
	float GetFrictionResistance();	//���C��R�̃Q�b�^�[

	void  RotateTexture();					//�摜�𒚓x�悭��]

	void CorrectPosition(Object& block, ContactPointVector collision, float angle);		//���W�̕␳

	float damping = 0.9f;									//�����W��

private:
	Circle circle;				//
	RigidBody body;										//������������������
	const float Stone_Friction = { 0.3 };	// ���C�W��

	BODY_BEHAVIOR behavior = BOUND;		//�΂̋����̏��
	int boundCounter = 0;				//���񐔃o�E���h������]�����ԂɂȂ�
	float oldVectorNum = 0;				//vector�̍����o�����߂̕ۑ��p

	bool now = false;
	ContactPointVector collision;
	float blockAngle;

	Object* m_Block = nullptr;

};
