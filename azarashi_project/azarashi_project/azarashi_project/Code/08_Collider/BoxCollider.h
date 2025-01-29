#pragma once
#include <DirectXMath.h>
#include <cmath>
#include "../08_Collider/Base_collision.h"
#define _USE_MATH_DEFINES
#include "../03_GameMainFile/Math.h"
using namespace std;


class BoxCollider:public BaseCollider
{
public:

	static ContactPointVector ColliderWithCircle(Object* p_Circle, Object* p_Box);//�l�p�Ɖ~�̓����蔻��(��ڂ̈�����circle�ŁA��ڂ̈�����box)
	static bool ColliderWithBox(Object* p_Box1, Object* p_Box2);				 //�l�p�Ǝl�p�̓����蔻��(��{�I��update���񂵂Ă���l�p�̕���p_Box1�ɂ���)

	//static bool IsColliderInRange(float circleposx, float circleposy,float Scaffoldposx, float Scaffoldposy,float wihtd , float height);	 //

private://�~�Ƃ̓����蔻��Ŏg��

	//static const float range_x;//�����蔻������͈�X
	//tatic const float range_y;//�����蔻������͈�Y

	//--------------------------�x�N�g���Ȃǂ̌v�Z�̊֐�--------------------------
	static DirectX::XMFLOAT2 RotatePosition(DirectX::XMFLOAT2, Radian);//��]�s��
	//----------------------------------------------------------------------------
};