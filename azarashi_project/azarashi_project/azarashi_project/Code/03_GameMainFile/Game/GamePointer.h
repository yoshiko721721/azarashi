#pragma once
#include "../../01_Direct3D/Object.h"
#include "../../02_Input/input.h"
#include "../../03_GameMainFile/RigidBody.h"
#include"../../08_Collider/Base_collision.h"
#include "GameBlock.h"

#define AZARASHI_PICTURE_CIRCLE L"Asset/pic/azarasi.png"
#define AZARASHI_PICTURE_STAND  L"Asset/pic/point.png"

struct Circle
{
	float radius; // 半径
	float velocityX; // 垂直方向の速度
	float velocityY; // 垂直方向の速度
};

class GamePointer :public Object
{
public:

	GamePointer() {};
	GamePointer(float posX, float posY, float sizeX, float sizeY) : Object(posX, posY, sizeX, sizeY) {};
	~GamePointer() { Uninit(); };
	void Init();  //初期化
	void Update();//更新


	float GetCircleRadius();		//半径のゲッター
	float GetFrictionResistance();	//摩擦抵抗のゲッター

	void  RotateTexture();					//画像を丁度よく回転
	AZA_MODE_NUMMBER azaNum = STAND;
	AZA_MODE_NUMMBER oldAzaNum = azaNum;


	bool isChangeMode();									//アザラシのモード比較
	void SetAzaNum(AZA_MODE_NUMMBER m_azaNum);				//アザラシの画像セット

	void CorrectPosition(Object& block, ContactPointVector collision, float angle);		//座標の補正

	float damping = 0.9f;									//減速係数

private:
	Circle circle;				//
	RigidBody body;										//物理挙動を持たせる
	const float AZARASHI_MODE[MODENUM] = { 0.1 , 0.9 };	// 摩擦係数

	BODY_BEHAVIOR behavior = BOUND;		//アザラシの挙動の状態
	int boundCounter = 0;				//一定回数バウンドしたら転がる状態になる
	float oldVectorNum = 0;				//vectorの差を出すための保存用

	bool now = false;
	ContactPointVector collision;
	float blockAngle;

	Object* m_Block = nullptr;

};
