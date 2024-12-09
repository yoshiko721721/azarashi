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
	DirectX::XMFLOAT2 hitcorners[12] = {//当たり判定をとる際の座標格納先
		{ 0, 0 }, //LeftBottom
		{ 0, 0 }, //RightBottom
		{ 0, 0 }, //RightTop
		{ 0, 0 }, //LeftTop
	};

	bool CheckCollision_Box_Circle(Object* p_player, Object* p_block);//四角と円の当たり判定
	bool CheckCollision_Box_Box(Object* p_player, float Scaffoldposx, float Scaffoldposy, float angle, float wihtd, float height);	 //四角と四角の当たり判定
	bool IsColliderInRange(float circleposx, float circleposy,float Scaffoldposx, float Scaffoldposy,float wihtd , float height);	 //

private://円との当たり判定で使う

	const float range_x = 50;//当たり判定を取る範囲X
	const float range_y = 100;//当たり判定を取る範囲Y

	//--------------------------------計算の関数----------------------------------
	DirectX::XMFLOAT2 RotatePosition(DirectX::XMFLOAT2,float);//回転行列
	//----------------------------------------------------------------------------
};