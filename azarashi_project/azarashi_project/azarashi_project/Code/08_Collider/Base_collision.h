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
	ClossPoint checkCollision;			//�����������ǂ�����Ԃ�bool
	DirectX::XMFLOAT2 closspoint;	//�~�̐ڒn�_
	float distanceSquared;			//�ڒn�_����~�̒��S�̐��K�����ꂽ�x�N�g��
};

class BaseCollider
{
public:
	virtual void ColliderWithBox() = 0;
	virtual void ColliderWithCircle() = 0;
private:
};



