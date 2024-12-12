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
	DirectX::XMFLOAT2 hitcorners[4] = {//当たり判定をとる際の座標格納先
		{ 0, 0 }, //LeftBottom
		{ 0, 0 }, //RightBottom
		{ 0, 0 }, //RightTop
		{ 0, 0 }, //LeftTop
	};

	ContactPointVector CheckCollision_Circle_Box(Object* p_player, float circleposx, float circleposy, float radius);//四角と円の当たり判定
	bool CheckCollision_Circle_Circle(Object* m_boxpointer, float circleposx, float circleposy, float radius);	 //四角と四角の当たり判定
	bool IsColliderInRange(float circleposx, float circleposy, float Scaffoldposx, float Scaffoldposy, float wihtd, float height);	 //

private://円との当たり判定で使う

	const float range_x = 50;//当たり判定を取る範囲X
	const float range_y = 100;//当たり判定を取る範囲Y

	//--------------------------ベクトルなどの計算の関数--------------------------
	DirectX::XMFLOAT2 RotatePosition(DirectX::XMFLOAT2, float);//回転行列
	DirectX::XMFLOAT2 SubtractVectors(const DirectX::XMFLOAT2 vec1, const DirectX::XMFLOAT2 vec2);//ベクトル計算
	float CrossProduct(DirectX::XMFLOAT2, DirectX::XMFLOAT2);//外積(多分使わんから消す)
	float dotProduct(DirectX::XMFLOAT2 v1, DirectX::XMFLOAT2 v2);//内積
	//----------------------------------------------------------------------------
};
