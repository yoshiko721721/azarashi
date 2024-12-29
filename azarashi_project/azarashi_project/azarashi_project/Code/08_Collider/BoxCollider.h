#pragma once
#include <DirectXMath.h>
#include <cmath>
#include "../08_Collider/Base_collision.h"
#define _USE_MATH_DEFINES
#include <math.h>
using namespace std;


class BoxCollider:public BaseCollider
{
public:
	static DirectX::XMFLOAT2 hitcorners[4];//�����蔻����Ƃ�ۂ̍��W�i�[

	static ContactPointVector ColliderWithCircle(Object* p_Circle,Object* p_Box);//�l�p�Ɖ~�̓����蔻��(��ڂ̈�����circle�ŁA��ڂ̈�����box)
	static bool ColliderWithBox(Object* p_Box1, Object* p_Box2);				 //�l�p�Ǝl�p�̓����蔻��(��{�I��update���񂵂Ă���l�p�̕���p_Box1�ɂ���)
	//static bool IsColliderInRange(float circleposx, float circleposy,float Scaffoldposx, float Scaffoldposy,float wihtd , float height);	 //

private://�~�Ƃ̓����蔻��Ŏg��

<<<<<<< HEAD
	static float range_x;//�����蔻������͈�X
	static float range_y;//�����蔻������͈�Y
=======
	//static const float range_x;//�����蔻������͈�X
	//tatic const float range_y;//�����蔻������͈�Y
>>>>>>> 55ad0e60c1cf48eabbd4b77e80a9963e15570d9c

	//--------------------------�x�N�g���Ȃǂ̌v�Z�̊֐�--------------------------
	static DirectX::XMFLOAT2 RotatePosition(DirectX::XMFLOAT2,float);//��]�s��
	static float dotProduct(DirectX::XMFLOAT2 v1, DirectX::XMFLOAT2 v2);//����
	//----------------------------------------------------------------------------
};