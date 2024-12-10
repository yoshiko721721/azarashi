#pragma once
#include <DirectXMath.h>
#include <cmath>
#include <math.h>
#include "../01_Direct3D/Object.h"
#define _USE_MATH_DEFINES

using namespace std;

class BoxCollider
{
public:
	DirectX::XMFLOAT2 hitcorners[12] = {//�����蔻����Ƃ�ۂ̍��W�i�[��
		{ 0, 0 }, //LeftBottom
		{ 0, 0 }, //RightBottom
		{ 0, 0 }, //RightTop
		{ 0, 0 }, //LeftTop
	};

	bool CheckCollision_Box_Circle(Object* p_player, float Scaffoldposx, float Scaffoldposy, float angle, float wihtd, float height);//�l�p�Ɖ~�̓����蔻��
	bool CheckCollision_Box_Box(Object* p_player, float Scaffoldposx, float Scaffoldposy, float angle, float wihtd, float height);	 //�l�p�Ǝl�p�̓����蔻��
	bool IsColliderInRange(float circleposx, float circleposy,float Scaffoldposx, float Scaffoldposy,float wihtd , float height);	 //

private://�~�Ƃ̓����蔻��Ŏg��

	const float range_x = 50;//�����蔻������͈�X
	const float range_y = 100;//�����蔻������͈�Y

	//--------------------------------�v�Z�̊֐�----------------------------------
	DirectX::XMFLOAT2 RotatePosition(DirectX::XMFLOAT2,float);//��]�s��
	//----------------------------------------------------------------------------
};