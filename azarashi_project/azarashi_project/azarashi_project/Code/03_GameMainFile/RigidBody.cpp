#include "RigidBody.h"
#include "../08_Collider/BoxCollider.h"
#include <iostream>

using namespace Math;

void RigidBody::Update()
{
	//TimeCounter(FRAMERATE);
}

//����������������������������������������������
//				����
//����������������������������������������������


/// <summary>
/// �p�x�𔽉f��������
/// </summary>
/// <param name="m_Velocity"></param>
/// <param name="m_Angle"></param>
void RigidBody::VectorPruductAngle(Vector2* m_Vector, float m_Angle, float friction)
{

}

//�^�C�}�[
void RigidBody::TimeCounter()
{
	time = (1 / FRAMERATE);
}

//���Ԃ̃��Z�b�g
void RigidBody::TimeReset()
{
	time = 0.01f;
}

//���R����
void RigidBody::FreeFall(float time)
{
	vector.y += -0.5 * g * time * mag;	//���x
}

//�����̌v�Z
void RigidBody::Repulsion()
{
	vectorNum = Math::CalcSquareRoot(vector.x, vector.y);
	float reflectedX = vectorNum * cos(fainalNormalAngle);
	float reflectedY = vectorNum * sin(fainalNormalAngle);

	vector.x = reflectedX * restitution;
	vector.y = reflectedY * restitution;

	vectorNum = Math::CalcSquareRoot(vector.x, vector.y);

	if (vectorNum < 0.8) {
		//vector.x = 0;
		vector.y = 0;
	}

}

//�͂̒ǉ�
void RigidBody::AddForce(float forceX, float forceY)
{
	vector.x += forceX;
	vector.y += forceY;
}

//�]���鏈��
void RigidBody::HorizonUpdate(Object& block, float friction)
{

	Vector2 normal;	//�@���x�N�g��
	normal.x = 1.0f * cos(fainalNormalAngle);
	normal.y = 1.0f * sin(fainalNormalAngle);

	//�@���x�N�g���̐��K��
	float magNormal = Math::CalcSquareRoot(normal.x, normal.y);
	normal.x /= magNormal;
	normal.y /= magNormal;

	//����
	Vector2 reflected;
	float dotProduct = (vector.x * normal.x + vector.y * normal.y);
	reflected.x = vector.x - 2 * dotProduct * normal.x;
	reflected.y = vector.y - 2 * dotProduct * normal.y;

	reflected = (1 - friction);

	Vector2 tangent = { -normal.y, normal.x };	//�ڐ��x�N�g��

	reflected.x += tangent.x * g;
	reflected.y += tangent.y * g;

	vector.x = reflected.x;
	vector.y = reflected.y;

}

void RigidBody::DampingVector(float m_damping, AZA_MODE_NUMMBER m_Mode_Nummber)
{
	if (m_Mode_Nummber == STAND) {
		vector.x -= vector.x * m_damping;
	}
	else if (m_Mode_Nummber == CIRCLE) {
		vector.x -= vector.x * (1 - m_damping);
	}
}

bool RigidBody::isHorizonOrVertical(float boxAngle)
{
	boxAngle = fmod(boxAngle, 360);
	if (boxAngle == 0 || boxAngle == 90 ||
		boxAngle == 180 || boxAngle == 270) {
		return true;
	}
	return false;
}

/// @brief �@���̊p�x�����߂�֐�
/// @param clossPoint �ڒn�_
/// @param circle �~�̏��
/// @param block �l�p�`�̏��
void RigidBody::CalcFainalNormalAngle(XMFLOAT2 clossPoint, Object& circle, Object& block)
{

	Vector2 normal = { circle.GetPos().x - clossPoint.x , circle.GetPos().y - clossPoint.y }; //�ڒn�_����~�̒��S�ւ̃x�N�g�����v�Z
	Vector2 normalVector = Math::Normalize(normal);				//���K�����ꂽ�@���x�N�g��
	float normalAngle = atan2(normalVector.y, normalVector.x);	//�@���x�N�g���̊p�x
	normalAngle = Math::MaintenanceRadian(normalAngle);			//�p�x�̃����e�i���X

	fainalNormalAngle = normalAngle;
	std::cout << "�@���̊p�x : " << normalAngle * Math::ConvertDegreeToMethod();


	std::cout << std::endl;

}



//==============================================
//				�Z�b�^�[
//==============================================

//����
void RigidBody::SetVector(float setVX, float setVY)
{
	vector.x = setVX;
	vector.y = setVY;
}

//����
void RigidBody::SetTime(float setTime)
{
	time = setTime;
}

//����
void RigidBody::SetMass(float setMass)
{
	mass = setMass;
}

//�s���̂����{��
void RigidBody::SetMag(float setMag)
{
	mag = setMag;
}

//==============================================
//				�Q�b�^�[
//==============================================


//����
Vector2 RigidBody::GetVector()
{
	return vector;
}

//����
float RigidBody::GetTime()
{
	return time;
}
//����
float RigidBody::GetMass()
{
	return mass;
}

//�s���̂����{��
float RigidBody::GetMag()
{
	return mag;
}

float RigidBody::GetFainalAngle()
{
	return fainalNormalAngle;
}
