#pragma once
#include "../../../01_Direct3D/Object.h"
#include "../../../02_Input/input.h"
#include "../../../03_GameMainFile/RigidBody.h"
#include"../../../08_Collider/Base_collision.h"
#include "../GameBlock.h"

class Stone :public Object
{
public:

	Stone() {};
	Stone(float posX, float posY, float sizeX, float sizeY) : Object(posX, posY, sizeX, sizeY) {};
	~Stone() { Uninit(); };
	void Init();  //初期化
	void Update();//更新


	float GetCircleRadius();		//半径のゲッター
	float GetFrictionResistance();	//摩擦抵抗のゲッター

	void  RotateTexture();					//画像を丁度よく回転

	void CorrectPosition(Object& block, ContactPointVector collision, float angle);		//座標の補正

	float damping = 0.9f;									//減速係数

private:
	Circle circle;				//
	RigidBody body;										//物理挙動を持たせる
	const float Stone_Friction = { 0.3 };	// 摩擦係数

	BODY_BEHAVIOR behavior = BOUND;		//石の挙動の状態
	int boundCounter = 0;				//一定回数バウンドしたら転がる状態になる
	float oldVectorNum = 0;				//vectorの差を出すための保存用

	bool now = false;
	ContactPointVector collision;
	float blockAngle;

	Object* m_Block = nullptr;

};
