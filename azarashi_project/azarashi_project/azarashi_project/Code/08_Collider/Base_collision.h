#pragma once
#include <DirectXMath.h>
#include <cmath>
#include "../01_Direct3D/Object.h"
#define _USE_MATH_DEFINES
#include <math.h>
using namespace std;

enum ClossPoint {
	NO_COLLISION,
	COLLISION,
	LEFTUP,
	RIGHTUP,
	LEFTDOWN,
	RIGHTDOWN
};

struct  ContactPointVector
{
	ClossPoint checkCollision;			//当たったかどうかを返すbool
	DirectX::XMFLOAT2 closspoint;	//円の接地点
	float distanceSquared;			//接地点から円の中心の正規化されたベクトル
};

class BaseCollider
{
public:
	virtual void ColliderWithBox() = 0;
	virtual void ColliderWithCircle() = 0;
private:
};



