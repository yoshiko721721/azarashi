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
/// @param clossPoint  �ڒn�_
/// @param normalAngle �@���̊p�x
struct DotVector {
	Vector2 pos;
	float normalAngle;
};

struct  ContactPointVector
{
	CollisionPoint checkCollision;	//�����������ǂ�����Ԃ�
	DotVector closspoint;			//�~�̐ڒn�_�Ɩ@���̊p�x��Ԃ�
	float distanceSquared;			//�ڒn�_����~�̒��S�̐��K�����ꂽ�x�N�g��
};

class BaseCollider
{
public:
	virtual void ColliderWithBox() = 0;
	virtual void ColliderWithCircle() = 0;
private:
};



