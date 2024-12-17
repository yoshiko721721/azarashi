#pragma once
#include <DirectXMath.h>
#include <cmath>
#include "../01_Direct3D/Object.h"
#define _USE_MATH_DEFINES
#include <math.h>
using namespace std;

struct  ContactPointVector
{
	bool checkCollision;			//�����������ǂ�����Ԃ�bool
	DirectX::XMFLOAT2 closspoint;	//�~�̐ڒn�_
	DirectX::XMFLOAT2 normalizedVector;//�ڒn�_����~�̒��S�̐��K�����ꂽ�x�N�g��
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


