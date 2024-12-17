#pragma once
#include <DirectXMath.h>
#include <cmath>
#include "Object.h"
#include "Base_collision.h"
#define _USE_MATH_DEFINES
#include <math.h>
using namespace std;


class BoxCollider:public BaseCollider
{
public:
	static DirectX::XMFLOAT2 hitcorners[4];//当たり判定をとる際の座標格納

	static ContactPointVector ColliderWithCircle(Object* p_player, float Scaffoldposx, float Scaffoldposy, float angle, float wihtd, float height);//四角と円の当たり判定
	static bool ColliderWithBox(Object* p_player, float Scaffoldposx, float Scaffoldposy, float angle, float wihtd, float height, DirectX::XMFLOAT2& touchbox);	 //四角と四角の当たり判定
	static bool IsColliderInRange(float circleposx, float circleposy,float Scaffoldposx, float Scaffoldposy,float wihtd , float height);	 //

private://円との当たり判定で使う

	static const float range_x;//当たり判定を取る範囲X
	static const float range_y;//当たり判定を取る範囲Y

	//--------------------------ベクトルなどの計算の関数--------------------------
	static DirectX::XMFLOAT2 RotatePosition(DirectX::XMFLOAT2,float);//回転行列
	static float dotProduct(DirectX::XMFLOAT2 v1, DirectX::XMFLOAT2 v2);//内積
	//----------------------------------------------------------------------------
};