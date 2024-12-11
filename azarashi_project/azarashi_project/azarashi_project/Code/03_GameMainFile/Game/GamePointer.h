#pragma once
#include "../../01_Direct3D/Object.h"
#include "../../02_Input/input.h"
#include "../../03_GameMainFile/RigidBody.h"
#include "GameBlock.h"

#define AZARASHI_PICTURE_CIRCLE L"Asset/pic/azarasi.png"
#define AZARASHI_PICTURE_STAND  L"Asset/pic/MatsuFace_transparent.png"



struct Circle
{
	//float x, y; // 位置
	float radius; // 半径
	float velocityX; // 垂直方向の速度
	float velocityY; // 垂直方向の速度
};

class GamePointer :public Object
{
public:
	RigidBody body;

	GamePointer() {}
	~GamePointer() { Uninit(); }
	void Init();  //初期化
	void Update(float blockAngle);//更新


	float GetCircleRadius();		//半径のゲッター
	float GetFrictionResistance();	//摩擦抵抗のゲッター
	
	void  RotateTexture(const float sub);					//画像を丁度よく回転
	AZA_MODE_NUMMBER azaNum = STAND;
	AZA_MODE_NUMMBER oldAzaNum = azaNum;


	bool isChangeMode();									//アザラシのモード比較
	void SetAzaNum(AZA_MODE_NUMMBER m_azaNum);				//アザラシの画像セット


	//float GetCirclePosX();
	//float GetCirclePosY();

	float damping = 0.9f;
private:
	Circle circle;
	const float AZARASHI_MODE[MODENUM] = { 0.3 , 0.2 };	// 摩擦係数
	//const float gravity = -0.4f;					// 重力の力
};

