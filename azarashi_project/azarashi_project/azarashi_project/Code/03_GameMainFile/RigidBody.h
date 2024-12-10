#pragma once
#include"../01_Direct3D/Object.h"
#include "Math.h"
using DirectX::XMFLOAT2;

//
//	基本的に重力加速度のような固定値にできるものも
//	レべルデザインの都合上変化する必要があるため
//	基本変数にしています。
//

const float g = 9.81f;			//重力加速度
const float restitution = 0.8f;	//反発係数


class RigidBody
{
private:

	float mass;				//質量
	float time;				//時間によって進む量が変わるため
	float mag;				//ゲームを自然にみせるための倍率

public:

	Vector2 vector;					//方向
	float vectorNum;				//総合的な速度
	bool oldCollisionFlg = false;	//二回連続で処理に入るときめり込まないようにするため

	//========================================
	//			常に必要・反映されるもの
	//========================================
	void Update(Vector2 position,float dt) ;	//更新処理
	void FreeFall(float setTime);				//自由落下


	//=======================================
	//			条件を満たした時に反映するもの
	//=======================================
	void Repulsion(float friction);											//反発
	void AddForce (float forceX,float forceY);								//力を加える
	void HorizonUpdate(Vector2* m_Velocity,float friction, float angle);	//減速の計算

	//角度に添ったベクトル変換
	void VectorPruductAngle(Vector2* m_Velocity,float angle, float friction);

	//ストップウォッチ
	void TimeCounter(float frameRate);
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

};

