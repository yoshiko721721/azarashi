#pragma once
#include <DirectXMath.h>
#include <cmath>
#define _USE_MATH_DEFINES
#include <math.h>
#include "../08_Collider/Base_collision.h"

class CircleCollider :public BaseCollider
{
public:
	static DirectX::XMFLOAT2 hitcorners[4];//�����蔻����Ƃ�ۂ̍��W�i�[��

	static ContactPointVector ColliderWithBox(Object* p_Box, Object* p_Circle);//�l�p�Ɖ~�̓����蔻��(��ڂ̈�����Box�ŁA��ڂ̈�����circle)
	static bool ColliderWithCircle(Object* p_Circle1, Object* p_Circle2);	   //�~�Ɖ~�̓����蔻��(��{�I��update���񂵂Ă���~�̕���p_circle1�ɂ���)
	static bool IsColliderInRange(float circleposx, float circleposy, float Scaffoldposx, float Scaffoldposy, float wihtd, float height);	 //

private://�~�Ƃ̓����蔻��Ŏg��

	static const float range_x;//�����蔻������͈�X
	static const float range_y;//�����蔻������͈�Y

	//--------------------------�x�N�g���Ȃǂ̌v�Z�̊֐�--------------------------
	static DirectX::XMFLOAT2 RotatePosition(DirectX::XMFLOAT2, float);//��]�s��
	static DirectX::XMFLOAT2 SubtractVectors(const DirectX::XMFLOAT2 vec1, const DirectX::XMFLOAT2 vec2);//�x�N�g���v�Z
	static float CrossProduct(DirectX::XMFLOAT2, DirectX::XMFLOAT2);//�O��(�����g��񂩂����)
	static float dotProduct(DirectX::XMFLOAT2 v1, DirectX::XMFLOAT2 v2);//����
	//----------------------------------------------------------------------------
};
