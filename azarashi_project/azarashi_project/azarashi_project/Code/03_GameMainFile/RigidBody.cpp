#include "RigidBody.h"
#include "../08_Collider/BoxCollider.h"
#include <iostream>

using namespace Math;

void RigidBody::Update()
{
	//TimeCounter(FRAMERATE);
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

}

//タイマー
void RigidBody::TimeCounter()
{
	time = (1 / FRAMERATE);
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

//反発の計算
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

//力の追加
void RigidBody::AddForce(float forceX, float forceY)
{
	vector.x += forceX;
	vector.y += forceY;
}

//転がる処理
void RigidBody::HorizonUpdate(Object& block, float friction)
{

	Vector2 normal;	//法線ベクトル
	normal.x = 1.0f * cos(fainalNormalAngle);
	normal.y = 1.0f * sin(fainalNormalAngle);

	//法線ベクトルの正規化
	float magNormal = Math::CalcSquareRoot(normal.x, normal.y);
	normal.x /= magNormal;
	normal.y /= magNormal;

	//内積
	Vector2 reflected;
	float dotProduct = (vector.x * normal.x + vector.y * normal.y);
	reflected.x = vector.x - 2 * dotProduct * normal.x;
	reflected.y = vector.y - 2 * dotProduct * normal.y;

	reflected = (1 - friction);

	Vector2 tangent = { -normal.y, normal.x };	//接線ベクトル

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

/// @brief 法線の角度を求める関数
/// @param clossPoint 接地点
/// @param circle 円の情報
/// @param block 四角形の情報
void RigidBody::CalcFainalNormalAngle(XMFLOAT2 clossPoint, Object& circle, Object& block)
{

	Vector2 normal = { circle.GetPos().x - clossPoint.x , circle.GetPos().y - clossPoint.y }; //接地点から円の中心へのベクトルを計算
	Vector2 normalVector = Math::Normalize(normal);				//正規化された法線ベクトル
	float normalAngle = atan2(normalVector.y, normalVector.x);	//法線ベクトルの角度
	normalAngle = Math::MaintenanceRadian(normalAngle);			//角度のメンテナンス

	fainalNormalAngle = normalAngle;
	std::cout << "法線の角度 : " << normalAngle * Math::ConvertDegreeToMethod();


	std::cout << std::endl;

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
void RigidBody::SetMass(float setMass)
{
	mass = setMass;
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

float RigidBody::GetFainalAngle()
{
	return fainalNormalAngle;
}
