#include "RigidBody.h"

using namespace Math;

void RigidBody::Update(Vector2 position,float dt)
{
	//���R����
	FreeFall(dt);
	
	
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
//	m_Angle += 90;
//	m_Angle *= ConvertDegreeToRadian();	//���g�̊p�x�����W�A���i�ʓx�@�j�ɂ���
//
//	vectorNum = vector.y;
//
//
//	m_Vector->x  = cos(m_Angle) * ( vectorNum );
//	m_Vector->y  = sin(m_Angle) * ( vectorNum );
//
}

//�^�C�}�[
void RigidBody::TimeCounter(float frameRate)
{
	time = (1 / frameRate);
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
//�������x�̌v�Z
void RigidBody::Repulsion(float friction, float angle)
{

	vector.y *= - (1.0 - restitution);


}
//�͂̒ǉ�
void RigidBody::AddForce(float forceX, float forceY)
{
	vector.x += forceX;
	vector.y += forceY;
}

//�]���鏈��
void RigidBody::HorizonUpdate(Vector2* m_Vector,float friction,float angle )
{
	Vector2 tempVector;
	float tempVectorNum;		//���R�����Ɛ����R�͂��ӎ�
	angle *= Math::ConvertDegreeToRadian();

	tempVectorNum = m_Vector->y * sin(angle);
	
	tempVector.x = cos(angle) * tempVectorNum * (1 - friction); 
	tempVector.y = sin(angle) * tempVectorNum * (1 - friction); 
	// ���C�̉e����ǉ� 
	tempVector.x *= (1.0f - friction);
	tempVector.x -= tempVector.x * (1.0f - friction);

	// �x�N�g�����X�V 
	m_Vector->x += tempVector.x ;
	m_Vector->y += tempVector.y ;

}

void RigidBody::DampingVector(float m_damping, AZA_MODE_NUMMBER m_Mode_Nummber)
{
	if (m_Mode_Nummber == STAND) {
		vector.x -= vector.x * m_damping;
	}
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
void RigidBody::SetMass			(float setMass)
{
	mass = setMass ;
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
