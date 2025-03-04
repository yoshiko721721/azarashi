#include "RigidBody.h"
#include "../08_Collider/BoxCollider.h"
#include <iostream>
#include <algorithm>

using namespace Math;
using namespace DirectX;

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



RigidBody::RigidBody()
{
}

//���R����
void RigidBody::FreeFall(float time)
{
	vector.y += -0.5 * g * time * mag;	//���x
}
//�����̌v�Z
void RigidBody::Repulsion()
{
	//���g�̃x�N�g���̌��������߂�
	Degree myAngle = Math::ConvertToDegree(atan2(vector.y, vector.x));
	Degree nrmAngleD = Math::ConvertToDegree(finalNormalAngle);


	Degree refrectAngleD = Math::CalcRefrectAngle(myAngle, nrmAngleD);

	if (nrmAngleD > 180.0f) {
		refrectAngleD += 180.0f;
	}

	vectorNum = Math::CalcSquareRoot(vector.x, vector.y);
	Radian refrectAngleR = ConvertToRadian(refrectAngleD);
	Vector2 refrected = { vectorNum * cosf( refrectAngleR ),
						  vectorNum * sinf( refrectAngleR )};

	//�����̈ړ��ʂ��v�Z
	vector.x = refrected.x * (1.0f - restitution);
	vector.y = refrected.y * (1.0f - restitution);

}
//�͂̒ǉ�
void RigidBody::AddForce(float forceX, float forceY)
{
	vector.x += forceX;
	vector.y += forceY;
}

//�]���鏈��
void RigidBody::HorizonUpdate(Object& player, Object& block, float friction, float speed)
{
	Vector2 velocity = 0;
	//���x���v�Z
	velocity.x = cosf( - finalNormalAngle) * speed * (1 - friction);
	velocity.y = sinf( - finalNormalAngle) * speed * (1 - friction);

	vector = velocity;

}

//�g���ĂȂ�
void RigidBody::DampingVector(float m_damping, AZA_MODE_NUMMBER m_Mode_Nummber)
{
	if (m_Mode_Nummber == STAND) {
		vector.x -= vector.x * m_damping;
	}
	else if (m_Mode_Nummber == CIRCLE) {
		vector.x -= vector.x * (1 - m_damping);
	}
}
//�g���ĂȂ�
bool RigidBody::isHorizonOrVertical(float boxAngle)
{
	//
	boxAngle = NormalizeDegree(boxAngle);
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

float RigidBody::CalcFinalNormalAngle(ContactPointVector collision, Object& circle, Object& block)
{
	if (collision.checkCollision != COLLISION) {
		// �ڒn�_����~�̒��S�ւ̃x�N�g�����v�Z
		Vector2 normal = { circle.GetPos().x - collision.closspoint.pos.x , circle.GetPos().y - collision.closspoint.pos.y };

		//�@���x�N�g���̊p�x
		Radian nrmAngleR = NormalizeRadian(atan2(normal.y, normal.x));	//0~360�ɐ��K��		
		Degree nrmAngleD = ConvertToDegree((nrmAngleR));

		// �Փˈʒu�ɉ����Ė@���x�N�g���̊p�x�𐧌�
		switch (collision.checkCollision) {
		case LEFTUP:	nrmAngleR = ConvertToRadian(clamp(nrmAngleD, 90 + block.GetAngle(), 180 + block.GetAngle())); break;
		case LEFTDOWN:	nrmAngleR = ConvertToRadian(clamp(nrmAngleD, 180 + block.GetAngle(), 270 + block.GetAngle())); break;
		case RIGHTUP:	nrmAngleR = ConvertToRadian(clamp(nrmAngleD, 0 + block.GetAngle(), 90 + block.GetAngle())); break;
		case RIGHTDOWN: nrmAngleR = ConvertToRadian(clamp(nrmAngleD, 270 + block.GetAngle(), 360 + block.GetAngle())); break;
		}

		// �ŏI�I�Ȗ@���x�N�g���̊p�x�𐳋K�����ĕێ�
		finalNormalAngle = nrmAngleR;
	}
	else {
		finalNormalAngle = Math::ConvertToRadian(collision.closspoint.normalAngle);
	}

	finalNormalAngle = Math::NormalizeRadian(finalNormalAngle);
	return finalNormalAngle;
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
float RigidBody::GetFinalAngle()
{
	return finalNormalAngle;
}
