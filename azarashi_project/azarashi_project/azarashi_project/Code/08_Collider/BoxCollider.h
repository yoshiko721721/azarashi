#pragma once
#include <DirectXMath.h>
#include <cmath>
#include "Bass_collision.h"
#define _USE_MATH_DEFINES
#include <math.h>
using namespace std;


class BoxCollider:public BaseCollider
{
public:
	DirectX::XMFLOAT2 hitcorners[4] = {//�����蔻����Ƃ�ۂ̍��W�i�[��
		{ 0, 0 }, //LeftBottom
		{ 0, 0 }, //RightBottom
		{ 0, 0 }, //RightTop
		{ 0, 0 }, //LeftTop
	};

	ContactPointVector ColliderWithCircle(Object* p_player, float Scaffoldposx, float Scaffoldposy, float angle, float wihtd, float height);//�l�p�Ɖ~�̓����蔻��
	bool ColliderWithBox(Object* p_player, float Scaffoldposx, float Scaffoldposy, float angle, float wihtd, float height, DirectX::XMFLOAT2& touchbox);	 //�l�p�Ǝl�p�̓����蔻��
	bool IsColliderInRange(float circleposx, float circleposy,float Scaffoldposx, float Scaffoldposy,float wihtd , float height);	 //

private://�~�Ƃ̓����蔻��Ŏg��

	const float range_x = 150;//�����蔻������͈�X
	const float range_y = 100;//�����蔻������͈�Y

	//--------------------------�x�N�g���Ȃǂ̌v�Z�̊֐�--------------------------
	DirectX::XMFLOAT2 RotatePosition(DirectX::XMFLOAT2,float);//��]�s��
	float dotProduct(DirectX::XMFLOAT2 v1, DirectX::XMFLOAT2 v2);//����
	//----------------------------------------------------------------------------
};