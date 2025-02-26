#pragma once
#include "../../01_Direct3D/Object.h"
#include "../../02_Input/input.h"
#include "../../08_Collider/BoxCollider.h"
#include "../../03_GameMainFile/Math.h"

const float groundY = 0.0f; // 地面のY座標
const float groundX = 0.0f; // 地面のY座標

enum HowHitPoints {
	HIT_NO,
	HIT_ONE,
	HIT_DOUBLE
};

class GameBlock :public Object
{
public:
	GameBlock();
	GameBlock(float posX, float posY, float sizeX, float sizeY);
	~GameBlock() { Uninit(); }
	void Init();  //初期化
	void Update();//更新

	float GetFrictionRasistance();
	float GetOldAngle();

	bool CheckCollision(Object& obj1, Object& obj2,Vector2& mtv);

	static float unificationFloorAngle;
	static float unificationWallAngle;
	static bool isCorrect;

protected:
	void CorrectPointerPosition(float angle);
	void CorrectStonePosition(float angle);
	void CorrectSnowmanPosition(float angle);
	void CorrectAngle(ContactPointVector collision, Object pointer);
	void CorrectAngle(Object& collision, Object& pointer);
	void CorrectBlockPosition(Object& perBlock,Object& haveBlock);

	//点と直線の距離を計算する関数
	//四角形同士の最短距離を計算する関数
private:
	ContactPointVector myCollision;
	ContactPointVector otherCollision[2];
	HowHitPoints hitPoint = HIT_NO;
	Object* hitObject[2];
	Object* m_Block;
	Object  oldMyBlock;
	Vector2 mtv;
	float oldAngle = GetAngle();
	float frictionRasistance;	//摩擦係数
};

