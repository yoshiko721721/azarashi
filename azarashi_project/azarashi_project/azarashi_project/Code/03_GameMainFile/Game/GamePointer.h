#pragma once
#include "../../01_Direct3D/Object.h"
#include "../../02_Input/input.h"
#include "../../03_GameMainFile/RigidBody.h"
#include "GameBlock.h"

class Circle
{
public:
	Vector2 position;		// ˆÊ’u
	float radius;			// ”¼Œa

};

class GamePointer :public Object
{
public:
	RigidBody body;

	GamePointer() {}
	~GamePointer() { Uninit(); }
	void Init();  //‰Šú‰»
	void Update();//XV


	//”¼Œa‚ÌƒQƒbƒ^[
	float GetCircleRadius();
	float GetFrictionResistance();



	void  RotateTexture(const float sub) ;	//‰æ‘œ‚ğ’š“x‚æ‚­‰ñ“]
	//float GetCirclePosX();
	//float GetCirclePosY();

private:
	Circle circle;
	const float frictionResistance = 0.5;		// –€CŒW”
	//const float gravity = -0.4f;				// d—Í‚Ì—Í
};

