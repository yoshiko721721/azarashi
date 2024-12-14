#pragma once
#include <DirectXMath.h>
#include <cmath>
#include "../01_Direct3D/Object.h"
#define _USE_MATH_DEFINES
#include <math.h>
using namespace std;

struct  ContactPointVector
{
	bool checkCollision; //当たったかの判定
	DirectX::XMFLOAT2 closspoint;//接地点
	DirectX::XMFLOAT2 normalizedVector;//接地点から円の中心までの
};
class BaseCollider
{
public:
	BaseCollider();
	~BaseCollider();
	virtual void ColliderWithBox() = 0;   //Boxとの当たり判定のベース関数
	virtual void ColliderWithCircle() = 0;//Circleとの当たり判定のベース関数

private:


};

