#pragma once
#include <DirectXMath.h>
#include <cmath>
#include "../01_Direct3D/Object.h"
#define _USE_MATH_DEFINES
#include <math.h>
using namespace std;

struct  ContactPointVector
{
	bool checkCollision; //�����������̔���
	DirectX::XMFLOAT2 closspoint;//�ڒn�_
	DirectX::XMFLOAT2 normalizedVector;//�ڒn�_����~�̒��S�܂ł�
};
class BaseCollider
{
public:
	BaseCollider();
	~BaseCollider();
	virtual void ColliderWithBox() = 0;   //Box�Ƃ̓����蔻��̃x�[�X�֐�
	virtual void ColliderWithCircle() = 0;//Circle�Ƃ̓����蔻��̃x�[�X�֐�

private:


};

