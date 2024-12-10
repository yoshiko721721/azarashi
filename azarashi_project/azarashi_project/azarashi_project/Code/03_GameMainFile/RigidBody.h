#pragma once
#include"../01_Direct3D/Object.h"
#include "Math.h"
using DirectX::XMFLOAT2;

//
//	��{�I�ɏd�͉����x�̂悤�ȌŒ�l�ɂł�����̂�
//	���׃��f�U�C���̓s����ω�����K�v�����邽��
//	��{�ϐ��ɂ��Ă��܂��B
//

const float g = 9.81f;			//�d�͉����x
const float restitution = 0.8f;	//�����W��


class RigidBody
{
private:

	float mass;				//����
	float time;				//���Ԃɂ���Đi�ޗʂ��ς�邽��
	float mag;				//�Q�[�������R�ɂ݂��邽�߂̔{��

public:

	Vector2 vector;					//����
	float vectorNum;				//�����I�ȑ��x
	bool oldCollisionFlg = false;	//���A���ŏ����ɓ���Ƃ��߂荞�܂Ȃ��悤�ɂ��邽��

	//========================================
	//			��ɕK�v�E���f��������
	//========================================
	void Update(Vector2 position,float dt) ;	//�X�V����
	void FreeFall(float setTime);				//���R����


	//=======================================
	//			�����𖞂��������ɔ��f�������
	//=======================================
	void Repulsion(float friction);											//����
	void AddForce (float forceX,float forceY);								//�͂�������
	void HorizonUpdate(Vector2* m_Velocity,float friction, float angle);	//�����̌v�Z

	//�p�x�ɓY�����x�N�g���ϊ�
	void VectorPruductAngle(Vector2* m_Velocity,float angle, float friction);

	//�X�g�b�v�E�H�b�`
	void TimeCounter(float frameRate);
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

};

