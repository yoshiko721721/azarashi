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
	static DirectX::XMFLOAT2 hitcorners[4];//当たり判定をとる際の座標格納

	static ContactPointVector ColliderWithCircle(Object* p_Circle,Object* p_Box);//四角と円の当たり判定(一つ目の引数がcircleで、二つ目の引数がbox)
	static bool ColliderWithBox(Object* p_Box1, Object* p_Box2);				 //四角と四角の当たり判定(基本的にupdateを回している四角の方をp_Box1にする)
	//static bool IsColliderInRange(float circleposx, float circleposy,float Scaffoldposx, float Scaffoldposy,float wihtd , float height);	 //

private://円との当たり判定で使う

<<<<<<< HEAD
	static float range_x;//当たり判定を取る範囲X
	static float range_y;//当たり判定を取る範囲Y
=======
	//static const float range_x;//当たり判定を取る範囲X
	//tatic const float range_y;//当たり判定を取る範囲Y
>>>>>>> 55ad0e60c1cf48eabbd4b77e80a9963e15570d9c

	//--------------------------ベクトルなどの計算の関数--------------------------
	static DirectX::XMFLOAT2 RotatePosition(DirectX::XMFLOAT2,float);//回転行列
	static float dotProduct(DirectX::XMFLOAT2 v1, DirectX::XMFLOAT2 v2);//内積
	//----------------------------------------------------------------------------
};