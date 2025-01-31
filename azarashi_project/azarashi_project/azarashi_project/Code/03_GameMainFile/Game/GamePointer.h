#pragma once
#include "../../01_Direct3D/Object.h"
#include "../../02_Input/input.h"
#include "../../02_Input/miyoshi_input/ControllerInput.h"
#include "../../03_GameMainFile/RigidBody.h"
#include"../../08_Collider/Base_collision.h"
#include "GameBlock.h"
#include "../../09_Sound/sound.h"

#define AZARASHI_PICTURE_CIRCLE L"Asset/pic/Player_Round.png"
#define AZARASHI_PICTURE_STAND  L"Asset/pic/azarasi.png"


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

	//テクスチャ用変数
	ID3D11ShaderResourceView* texture_Circle;
	ID3D11ShaderResourceView* texture_Stand;

	bool isChangeMode();									//アザラシのモード比較
	void SetAzaNum(AZA_MODE_NUMMBER m_azaNum);				//アザラシの画像セット

	void CorrectPosition(Object& block, ContactPointVector collision, float angle);		//座標の補正

	int GetNowHits();
	void NowHitsCounter(int count);

	Object* GetHitGameBlock(int objCount);

	float damping = 0.9f;									//減速係数

private:
	Circle circle;				//
	RigidBody body;										//物理挙動を持たせる
	const float AZARASHI_MODE[MODENUM] = { 0.1 , 0.9 };	// 摩擦係数

	BODY_BEHAVIOR behavior = BOUND;		//アザラシの挙動の状態
	int boundCounter = 0;				//一定回数バウンドしたら転がる状態になる
	float oldVectorNum = 0;				//vectorの差を出すための保存用

	int now ;
	ContactPointVector collision;
	ContactPointVector myCollision;
	float blockAngle;

	Object* m_Block = nullptr;
	Object* m_Blocks[2] = { nullptr,nullptr };
};
