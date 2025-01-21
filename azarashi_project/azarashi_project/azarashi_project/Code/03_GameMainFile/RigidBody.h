#pragma once
#include"../01_Direct3D/Object.h"
#include"../08_Collider/Base_collision.h"
#include "Math.h"
using DirectX::XMFLOAT2;

//
//	��{�I�ɏd�͉����x�̂悤�ȌŒ�l�ɂł�����̂�
//	���׃��f�U�C���̓s����ω�����K�v�����邽��
//	��{�ϐ��ɂ��Ă��܂��B
//

enum AZA_MODE_NUMMBER {
	CIRCLE = 0,
	STAND = 1,
	MODENUM = 2
};

const float g = 9.81f;			//�d�͉����x
const float restitution = 0.6;	//�����W��


class RigidBody
{
private:

	float mass;				//����
	float time;				//���Ԃɂ���Đi�ޗʂ��ς�邽��
	float mag;				//�Q�[�������R�ɂ݂��邽�߂̔{��
	float fainalNormalAngle;		//�Փ˂��N���������̍ŏI�I�Ȗ@���p�x
	bool edgeFlg;


public:

	Vector2 vector;					//����
	float vectorNum;				//�����I�ȑ��x

	Vector2 normalVector;			//�@���x�N�g��

	//========================================
	//			��ɕK�v�E���f��������
	//========================================
	void Update();	//�X�V����
	void FreeFall(float setTime);				//���R����


	//=======================================
	//			�����𖞂��������ɔ��f�������
	//=======================================
	void Repulsion();				//����
	void AddForce(float forceX, float forceY);									//�͂�������
	void HorizonUpdate(Object& block, float friction);	//�p�x���l������v�Z
	void DampingVector(float m_damping, AZA_MODE_NUMMBER m_Mode_Nummber);		//��������

	bool isHorizonOrVertical(float boxAngle);									//0�x�ɑ΂��Đ������������̊m�F
	void CalcFainalNormalAngle(XMFLOAT2 collision, Object& circle, Object& block);


	//�p�x�ɓY�����x�N�g���ϊ�
	void VectorPruductAngle(Vector2* m_Vector, float angle, float friction);

	//�X�g�b�v�E�H�b�`
	void TimeCounter();
	void TimeReset();

	//�Z�b�^�[
	void SetVector(float setVX, float setVY);		 //���x
	void SetMass(float setMass);					 //����
	void SetTime(float setTime);					 //����
	void SetMag(float setMag);						 //�Q�[�������R�ɂ݂��邽�߂̔{��

	//�Q�b�^�[
	Vector2 GetVector();			//���x
	float GetMass();				//����
	float GetTime();				//����
	float GetMag();					//�Q�[�������R�ɂ݂��邽�߂̔{��
	float GetFainalAngle();			//�@���̊p�x��Ԃ�
};


