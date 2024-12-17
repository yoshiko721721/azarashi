#pragma once
#include <DirectXMath.h>
#include <cmath>
#include "../01_Direct3D/Object.h"
#define _USE_MATH_DEFINES
#include <math.h>
using namespace std;

struct  ContactPointVector
{
	bool checkCollision;			//当たったかどうかを返すbool
	DirectX::XMFLOAT2 closspoint;	//円の接地点
	DirectX::XMFLOAT2 normalizedVector;//接地点から円の中心の正規化されたベクトル
};

class BaseCollider
{
public:
	BaseCollider();
	~BaseCollider();
	virtual void ColliderWithBox() = 0;
	virtual void ColliderWithCircle() = 0;

private:


};

BaseCollider::BaseCollider()
{
}

BaseCollider::~BaseCollider()
{
}


