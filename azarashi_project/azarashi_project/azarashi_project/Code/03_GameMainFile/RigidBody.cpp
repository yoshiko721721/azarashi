#include "RigidBody.h"

using namespace Math;

void RigidBody::Update(Vector2 position,float dt)
{
	//自由落下
	FreeFall(dt);

}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//				時間
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝


/// <summary>
/// 角度を反映した処理
/// </summary>
/// <param name="m_Velocity"></param>
/// <param name="m_Angle"></param>
void RigidBody::VectorPruductAngle(Vector2* m_Velocity, float m_Angle, float friction)
{
	m_Angle += 90;
	m_Angle *= ConvertDegreeToRadian();

	vectorNum = vector.y;


	m_Velocity->x  = cos(m_Angle) * ( vectorNum );
	m_Velocity->y  = sin(m_Angle) * ( vectorNum );

}

//タイマー
void RigidBody::TimeCounter(float frameRate)
{
	time = (1 / frameRate);
}
//時間のリセット
void RigidBody::TimeReset()
{
	time = 0.01f;
}
//自由落下
void RigidBody::FreeFall(float time)
{
	vector.y += -0.5 * g * time * mag;	//速度
}
//反発速度の計算
void RigidBody::Repulsion(float friction)
{
	//反発
	vector.y *= - restitution ;
}
//力の追加
void RigidBody::AddForce(float forceX, float forceY)
{
	vector.x += forceX;
	vector.y += forceY;
}

//転がる処理
void RigidBody::HorizonUpdate(Vector2* m_Velocity,float friction,float angle )
{

	//vectorNum = m_Velocity->y / sin(angle);
	//m_Velocity->x += cos(angle) * vectorNum;

	////垂直抗力を計算
	//float normaleForce = mass * g;
	////摩擦力を計算
	//float frictionForce = friction * normaleForce;
	//if (Math::ConvertAbsoluteValue(m_Velocity->x) > 0) {
	//	float deceleration = frictionForce / mass;
	//	if (Math::ConvertAbsoluteValue(m_Velocity->x <= deceleration * time)) {
	//		m_Velocity->x = 0;
	//	}
	//	else if(angle < 90){
	//		m_Velocity->x -= deceleration * time * (vector.x > 0 ? 1 : -1);
	//	}
	//	else if(angle > 90){
	//		m_Velocity->x = deceleration * time * (vector.x > 0 ? 1 : -1);
	//	}
	//}

}

void RigidBody::SetVector(float setVX, float setVY)
{
	vector.x = setVX;
	vector.y = setVY;
}
void RigidBody::SetTime(float setTime)
{
	time = setTime;
}
void RigidBody::SetMass			(float setMass)
{
	mass = setMass ;
}
void RigidBody::SetMag(float setMag)
{
	mag = setMag;
}

//ゲッター
float RigidBody::GetMass()
{
	return mass;
}
Vector2 RigidBody::GetVector()
{
	return vector;
}
float RigidBody::GetTime()
{
	return time;
}
float RigidBody::GetMag()
{
	return mag;
}
