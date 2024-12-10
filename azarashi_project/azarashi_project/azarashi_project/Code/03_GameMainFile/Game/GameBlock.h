#pragma once
#include "../../01_Direct3D/Object.h"
#include "../../02_Input/input.h"
#include "../../08_BoxCollider/BoxCollider.h"

	const float groundY = -200.0f; // 地面のY座標
	const float groundX = 0.0f; // 地面のY座標

class GameBlock :public Object
{
public:
	GameBlock() {}
	~GameBlock() { Uninit(); }
	void Init();  //初期化
	void Update();//更新

	float GetFrictionRasistance();
	BoxCollider collider;

private:

	float frictionRasistance;	//摩擦係数
};

