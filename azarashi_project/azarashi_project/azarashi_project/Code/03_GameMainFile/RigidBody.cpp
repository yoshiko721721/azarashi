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
void RigidBody::VectorPruductAngle(Vector2* m_Vector, float m_Angle, float friction)
{
//	m_Angle += 90;
//	m_Angle *= ConvertDegreeToRadian();	//自身の角度をラジアン（弧度法）にする
//
//	vectorNum = vector.y;
//
//
//	m_Vector->x  = cos(m_Angle) * ( vectorNum );
//	m_Vector->y  = sin(m_Angle) * ( vectorNum );
//
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
void RigidBody::Repulsion(float friction, float angle)
{

	vector.y *= - (1.0 - restitution);


}
//力の追加
void RigidBody::AddForce(float forceX, float forceY)
{
	vector.x += forceX;
	vector.y += forceY;
}

//転がる処理
void RigidBody::HorizonUpdate(Vector2* m_Vector,float friction,float angle )
{
	Vector2 tempVector;
	float tempVectorNum;		//自由落下と垂直抗力を意識
	angle *= Math::ConvertDegreeToRadian();

	tempVectorNum = m_Vector->y * sin(angle);
	
	tempVector.x = cos(angle) * tempVectorNum * (1 - friction); 
	tempVector.y = sin(angle) * tempVectorNum * (1 - friction); 
	// 摩擦の影響を追加 
	tempVector.x *= (1.0f - friction);
	tempVector.x -= tempVector.x * (1.0f - friction);

	// ベクトルを更新 
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
//				セッター
//==============================================

//方向
void RigidBody::SetVector(float setVX, float setVY)
{
	vector.x = setVX;
	vector.y = setVY;
}

//時間
void RigidBody::SetTime(float setTime)
{
	time = setTime;
}

//質量
void RigidBody::SetMass			(float setMass)
{
	mass = setMass ;
}

//都合のいい倍率
void RigidBody::SetMag(float setMag)
{
	mag = setMag;
}

//==============================================
//				ゲッター
//==============================================


//方向
Vector2 RigidBody::GetVector()
{
	return vector;
}

//時間
float RigidBody::GetTime()
{
	return time;
}
//質量
float RigidBody::GetMass()
{
	return mass;
}

//都合のいい倍率
float RigidBody::GetMag()
{
	return mag;
}
