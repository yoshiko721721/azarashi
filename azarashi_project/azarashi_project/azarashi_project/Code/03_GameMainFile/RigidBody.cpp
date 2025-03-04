#include "RigidBody.h"
#include "../08_Collider/BoxCollider.h"
#include <iostream>
#include <algorithm>

using namespace Math;
using namespace DirectX;

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



RigidBody::RigidBody()
{
}

//自由落下
void RigidBody::FreeFall(float time)
{
	vector.y += -0.5 * g * time * mag;	//速度
}
//反発の計算
void RigidBody::Repulsion()
{
	//自身のベクトルの向きを求める
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

	//反発の移動量を計算
	vector.x = refrected.x * (1.0f - restitution);
	vector.y = refrected.y * (1.0f - restitution);

}
//力の追加
void RigidBody::AddForce(float forceX, float forceY)
{
	vector.x += forceX;
	vector.y += forceY;
}

//転がる処理
void RigidBody::HorizonUpdate(Object& player, Object& block, float friction, float speed)
{
	Vector2 velocity = 0;
	//速度を計算
	velocity.x = cosf( - finalNormalAngle) * speed * (1 - friction);
	velocity.y = sinf( - finalNormalAngle) * speed * (1 - friction);

	vector = velocity;

}

//使ってない
void RigidBody::DampingVector(float m_damping, AZA_MODE_NUMMBER m_Mode_Nummber)
{
	if (m_Mode_Nummber == STAND) {
		vector.x -= vector.x * m_damping;
	}
	else if (m_Mode_Nummber == CIRCLE) {
		vector.x -= vector.x * (1 - m_damping);
	}
}
//使ってない
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

/// @brief 法線の角度を求める関数
/// @param clossPoint 接地点
/// @param circle 円の情報
/// @param block 四角形の情報

float RigidBody::CalcFinalNormalAngle(ContactPointVector collision, Object& circle, Object& block)
{
	if (collision.checkCollision != COLLISION) {
		// 接地点から円の中心へのベクトルを計算
		Vector2 normal = { circle.GetPos().x - collision.closspoint.pos.x , circle.GetPos().y - collision.closspoint.pos.y };

		//法線ベクトルの角度
		Radian nrmAngleR = NormalizeRadian(atan2(normal.y, normal.x));	//0~360に正規化		
		Degree nrmAngleD = ConvertToDegree((nrmAngleR));

		// 衝突位置に応じて法線ベクトルの角度を制限
		switch (collision.checkCollision) {
		case LEFTUP:	nrmAngleR = ConvertToRadian(clamp(nrmAngleD, 90 + block.GetAngle(), 180 + block.GetAngle())); break;
		case LEFTDOWN:	nrmAngleR = ConvertToRadian(clamp(nrmAngleD, 180 + block.GetAngle(), 270 + block.GetAngle())); break;
		case RIGHTUP:	nrmAngleR = ConvertToRadian(clamp(nrmAngleD, 0 + block.GetAngle(), 90 + block.GetAngle())); break;
		case RIGHTDOWN: nrmAngleR = ConvertToRadian(clamp(nrmAngleD, 270 + block.GetAngle(), 360 + block.GetAngle())); break;
		}

		// 最終的な法線ベクトルの角度を正規化して保持
		finalNormalAngle = nrmAngleR;
	}
	else {
		finalNormalAngle = Math::ConvertToRadian(collision.closspoint.normalAngle);
	}

	finalNormalAngle = Math::NormalizeRadian(finalNormalAngle);
	return finalNormalAngle;
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
float RigidBody::GetFinalAngle()
{
	return finalNormalAngle;
}
