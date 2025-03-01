#pragma once
#include <DirectXMath.h>
#include <cmath>
#include "../01_Direct3D/Object.h"
#include "../03_GameMainFile/Math.h"
#define _USE_MATH_DEFINES
#include <math.h>
using namespace std;

enum CollisionPoint {
	NO_COLLISION,
	COLLISION,
	LEFTUP,
	RIGHTUP,
	LEFTDOWN,
	RIGHTDOWN
};

/// @brief 
/// @param clossPoint  接地点
/// @param normalAngle 法線の角度
struct DotVector {
	Vector2 pos;
	float normalAngle;
};

struct  ContactPointVector
{
	CollisionPoint checkCollision;	//当たったかどうかを返す
	DotVector closspoint;			//円の接地点と法線の角度を返す
	float distanceSquared;			//接地点から円の中心の正規化されたベクトル
};

class BaseCollider
{
public:
	virtual void ColliderWithBox() = 0;
	virtual void ColliderWithCircle() = 0;
private:
};



