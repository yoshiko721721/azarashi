#pragma once
#include <DirectXMath.h>
#include <cmath>
#include "../01_Direct3D/Object.h"
#define _USE_MATH_DEFINES
#include <math.h>
using namespace std;

struct  ContactPointVector
{
	bool checkCollision;
	DirectX::XMFLOAT2 closspoint;
	DirectX::XMFLOAT2 normalizedVector;
};

class CircleCollider
{
public:
	DirectX::XMFLOAT2 hitcorners[4] = {//�����蔻����Ƃ�ۂ̍��W�i�[��
		{ 0, 0 }, //LeftBottom
		{ 0, 0 }, //RightBottom
		{ 0, 0 }, //RightTop
		{ 0, 0 }, //LeftTop
	};

	ContactPointVector CheckCollision_Circle_Box(Object* p_player, float circleposx, float circleposy, float radius);//�l�p�Ɖ~�̓����蔻��
	bool CheckCollision_Circle_Circle(Object* m_boxpointer, float circleposx, float circleposy, float radius);	 //�l�p�Ǝl�p�̓����蔻��
	bool IsColliderInRange(float circleposx, float circleposy, float Scaffoldposx, float Scaffoldposy, float wihtd, float height);	 //

private://�~�Ƃ̓����蔻��Ŏg��

	const float range_x = 50;//�����蔻������͈�X
	const float range_y = 100;//�����蔻������͈�Y

	//--------------------------�x�N�g���Ȃǂ̌v�Z�̊֐�--------------------------
	DirectX::XMFLOAT2 RotatePosition(DirectX::XMFLOAT2, float);//��]�s��
	DirectX::XMFLOAT2 SubtractVectors(const DirectX::XMFLOAT2 vec1, const DirectX::XMFLOAT2 vec2);//�x�N�g���v�Z
	float CrossProduct(DirectX::XMFLOAT2, DirectX::XMFLOAT2);//�O��(�����g��񂩂����)
	float dotProduct(DirectX::XMFLOAT2 v1, DirectX::XMFLOAT2 v2);//����
	//----------------------------------------------------------------------------
};
