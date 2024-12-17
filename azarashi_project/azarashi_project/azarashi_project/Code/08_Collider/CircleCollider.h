#pragma once
#include <DirectXMath.h>
#include <cmath>
#include "Object.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "Base_collision.h"

class CircleCollider :public BaseCollider
{
public:
	static DirectX::XMFLOAT2 hitcorners[4];//�����蔻����Ƃ�ۂ̍��W�i�[��

	static ContactPointVector ColliderWithBox(Object* p_player, float circleposx, float circleposy, float radius);//�l�p�Ɖ~�̓����蔻��
	static bool ColliderWithCircle(Object* m_boxpointer, float circleposx, float circleposy, float radius);	 //�l�p�Ǝl�p�̓����蔻��
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
