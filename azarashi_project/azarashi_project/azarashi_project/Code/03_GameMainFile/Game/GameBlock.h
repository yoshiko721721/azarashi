#pragma once
#include "../../01_Direct3D/Object.h"
#include "../../02_Input/input.h"
#include "../../08_Collider/BoxCollider.h"
#include "../../03_GameMainFile/Math.h"

const float groundY = 0.0f; // 地面のY座標
const float groundX = 0.0f; // 地面のY座標

enum HowHitPoints {
	NO_HIT,
	MY_ONLY,
	DOUBLE_HITS
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
protected:
	void CorrectPointerPosition(float angle);
	void CorrectStonePosition(float angle);
	void CorrectSnowmanPosition(float angle);

	void CorrectAngle(ContactPointVector collision, Object pointer);

private:
	ContactPointVector myCollision;
	ContactPointVector otherCollision[2];
	HowHitPoints hitPoint = NO_HIT;
	Object* hitObject[2];

	float oldAngle = GetAngle();
	float frictionRasistance;	//摩擦係数
};

