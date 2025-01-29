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

	GamePointer() {};
	GamePointer(float posX, float posY, float sizeX, float sizeY) : Object(posX, posY, sizeX, sizeY) {};
	~GamePointer() { Uninit(); };
	void Init();  //������
	void Update();//�X�V


	float GetCircleRadius();		//���a�̃Q�b�^�[
	float GetFrictionResistance();	//���C��R�̃Q�b�^�[

	void  RotateTexture();					//�摜�𒚓x�悭��]
	AZA_MODE_NUMMBER azaNum = STAND;
	AZA_MODE_NUMMBER oldAzaNum = azaNum;


	bool isChangeMode();									//�A�U���V�̃��[�h��r
	void SetAzaNum(AZA_MODE_NUMMBER m_azaNum);				//�A�U���V�̉摜�Z�b�g

	void CorrectPosition(Object& block, ContactPointVector collision, float angle);		//���W�̕␳

	float damping = 0.9f;									//�����W��

private:
	Circle circle;				//
	RigidBody body;										//������������������
	const float AZARASHI_MODE[MODENUM] = { 0.1 , 0.9 };	// ���C�W��

	BODY_BEHAVIOR behavior = BOUND;		//�A�U���V�̋����̏��
	int boundCounter = 0;				//���񐔃o�E���h������]�����ԂɂȂ�
	float oldVectorNum = 0;				//vector�̍����o�����߂̕ۑ��p

	bool now = false;
	ContactPointVector collision;
	float blockAngle;

	Object* m_Block = nullptr;

};
