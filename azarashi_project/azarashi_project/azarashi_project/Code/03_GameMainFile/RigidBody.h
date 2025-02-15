#pragma once
#include"../01_Direct3D/Object.h"
#include"../08_Collider/Base_collision.h"
#include "Math.h"
using DirectX::XMFLOAT2;

//
//	基本的に重力加速度のような固定値にできるものも
//	レべルデザインの都合上変化する必要があるため
//	基本変数にしています。
//

enum AZA_MODE_NUMMBER {
	CIRCLE = 0,
	STAND = 1,
	MODENUM = 2
};

enum BODY_BEHAVIOR {
	BOUND = 0,
	ROLLING = 1,
};

const float g = 9.81f;			//重力加速度
const float restitution = 0.6;	//反発係数


class RigidBody
{
private:

	float mass;				//質量
	float time;				//時間によって進む量が変わるため
	float mag;				//ゲームを自然にみせるための倍率
	bool edgeFlg;
	float oldNormalAngle = 0;

public:

	float finalNormalAngle;		//衝突が起こった時の最終的な法線角度
	float vectorNum;				//総合的な速度
	Vector2 vector = 0;					//方向
	Vector2 normalVector = 0;			//法線ベクトル

	RigidBody();

	//========================================
	//			常に必要・反映されるもの
	//========================================
	void FreeFall(float setTime);				//自由落下


	//=======================================
	//			条件を満たした時に反映するもの
	//=======================================
	void Repulsion();				//反発
	void AddForce(float forceX, float forceY);									//力を加える
	void HorizonUpdate(Object& player, Object& block, float friction, float speed);	//角度を考慮する計算
	void DampingVector(float m_damping, AZA_MODE_NUMMBER m_Mode_Nummber);		//減速処理

	bool isHorizonOrVertical(float boxAngle);									//0度に対して水平か垂直かの確認
	void CalcFinalNormalAngle(ContactPointVector collision, Object& circle, Object& block);		//法線ベクトルの計算
	void VectorPruductAngle(Vector2* m_Vector, float angle, float friction);	//角度に添ったベクトル変換


	//ストップウォッチ
	void TimeCounter();
	void TimeReset();

	//セッター
	void SetVector(float setVX, float setVY);		 //速度
	void SetMass(float setMass);					 //質量
	void SetTime(float setTime);					 //時間
	void SetMag(float setMag);						 //ゲームを自然にみせるための倍率

	//ゲッター
	Vector2 GetVector();			//速度
	float GetMass();				//質量
	float GetTime();				//時間
	float GetMag();					//ゲームを自然にみせるための倍率
	float GetFinalAngle();			//法線の角度を返す
};

