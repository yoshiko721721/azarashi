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
	static DirectX::XMFLOAT2 hitcorners[4];//“–‚½‚è”»’è‚ğ‚Æ‚éÛ‚ÌÀ•WŠi”[

	static ContactPointVector ColliderWithCircle(Object* p_player, float Scaffoldposx, float Scaffoldposy, float angle, float wihtd, float height);//lŠp‚Æ‰~‚Ì“–‚½‚è”»’è
	static bool ColliderWithBox(Object* p_player, float Scaffoldposx, float Scaffoldposy, float angle, float wihtd, float height, DirectX::XMFLOAT2& touchbox);	 //lŠp‚ÆlŠp‚Ì“–‚½‚è”»’è
	static bool IsColliderInRange(float circleposx, float circleposy,float Scaffoldposx, float Scaffoldposy,float wihtd , float height);	 //

private://‰~‚Æ‚Ì“–‚½‚è”»’è‚Åg‚¤

	static const float range_x;//“–‚½‚è”»’è‚ğæ‚é”ÍˆÍX
	static const float range_y;//“–‚½‚è”»’è‚ğæ‚é”ÍˆÍY

	//--------------------------ƒxƒNƒgƒ‹‚È‚Ç‚ÌŒvZ‚ÌŠÖ”--------------------------
	static DirectX::XMFLOAT2 RotatePosition(DirectX::XMFLOAT2,float);//‰ñ“]s—ñ
	static float dotProduct(DirectX::XMFLOAT2 v1, DirectX::XMFLOAT2 v2);//“àÏ
	//----------------------------------------------------------------------------
};