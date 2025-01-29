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

	static ContactPointVector ColliderWithCircle(Object* p_Circle, Object* p_Box);//四角と円の当たり判定(一つ目の引数がcircleで、二つ目の引数がbox)
	static bool ColliderWithBox(Object* p_Box1, Object* p_Box2);				 //四角と四角の当たり判定(基本的にupdateを回している四角の方をp_Box1にする)

	//static bool IsColliderInRange(float circleposx, float circleposy,float Scaffoldposx, float Scaffoldposy,float wihtd , float height);	 //

private://円との当たり判定で使う

	//static const float range_x;//当たり判定を取る範囲X
	//tatic const float range_y;//当たり判定を取る範囲Y

	//--------------------------ベクトルなどの計算の関数--------------------------
	static DirectX::XMFLOAT2 RotatePosition(DirectX::XMFLOAT2, Radian);//回転行列
	//----------------------------------------------------------------------------
};