#pragma once
#include <DirectXMath.h>
#include <cmath>
#include "../01_Direct3D/Object.h"
#define _USE_MATH_DEFINES
#include <math.h>
using namespace std;

static struct  ContactPointVector
{
	bool checkCollision;			//�����������ǂ�����Ԃ�bool
	DirectX::XMFLOAT2 closspoint;	//�~�̐ڒn�_
	DirectX::XMFLOAT2 normalizedVector;//�ڒn�_����~�̒��S�̐��K�����ꂽ�x�N�g��
};

class BaseCollider
{
public:
<<<<<<< HEAD
	//BaseCollider();
	//~BaseCollider();
=======
>>>>>>> 55ad0e60c1cf48eabbd4b77e80a9963e15570d9c
	virtual void ColliderWithBox() = 0;
	virtual void ColliderWithCircle() = 0;
private:
};
<<<<<<< HEAD
//
//BaseCollider::BaseCollider()
//{
//}
//
//BaseCollider::~BaseCollider()
//{
//}
=======

>>>>>>> 55ad0e60c1cf48eabbd4b77e80a9963e15570d9c


