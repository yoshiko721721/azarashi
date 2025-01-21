#pragma once
#include "../../01_Direct3D/Object.h"
#include "../../02_Input/input.h"
#include "../../03_GameMainFile/RigidBody.h"
#include"../../08_Collider/Base_collision.h"
#include "GameBlock.h"

#define AZARASHI_PICTURE_CIRCLE L"Asset/pic/azarasi.png"
#define AZARASHI_PICTURE_STAND  L"Asset/pic/point.png"

struct Circle
{
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
	void Update(ContactPointVector contactPointVector, Object& block);//�X�V


	float GetCircleRadius();		//���a�̃Q�b�^�[
	float GetFrictionResistance();	//���C��R�̃Q�b�^�[

	void  RotateTexture(const float sub);					//�摜�𒚓x�悭��]
	AZA_MODE_NUMMBER azaNum = STAND;
	AZA_MODE_NUMMBER oldAzaNum = azaNum;

	bool isChangeMode();									//�A�U���V�̃��[�h��r
	void SetAzaNum(AZA_MODE_NUMMBER m_azaNum);				//�A�U���V�̉摜�Z�b�g

	void CorrectPosition(Object* m_Block, XMFLOAT2 clossPoint, float distanceSquared, float angle);		//���W�̕␳

	float damping = 0.9f;
private:
	Circle circle;
	const float AZARASHI_MODE[MODENUM] = { 0.3 , 0.2 };	// ���C�W��

	bool old = false;
	bool now = false;
	//const float gravity = -0.4f;					// �d�̗͂�
};
