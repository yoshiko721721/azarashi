#pragma once
#include <DirectXMath.h>
#include <cmath>
#include "Bass_collision.h"
#define _USE_MATH_DEFINES
#include <math.h>
using namespace std;


class BoxCollider:public BaseCollider
{
public:
	DirectX::XMFLOAT2 hitcorners[4] = {//“–‚½‚è”»’è‚ğ‚Æ‚éÛ‚ÌÀ•WŠi”[æ
		{ 0, 0 }, //LeftBottom
		{ 0, 0 }, //RightBottom
		{ 0, 0 }, //RightTop
		{ 0, 0 }, //LeftTop
	};

	ContactPointVector ColliderWithCircle(Object* p_player, float Scaffoldposx, float Scaffoldposy, float angle, float wihtd, float height);//lŠp‚Æ‰~‚Ì“–‚½‚è”»’è
	bool ColliderWithBox(Object* p_player, float Scaffoldposx, float Scaffoldposy, float angle, float wihtd, float height, DirectX::XMFLOAT2& touchbox);	 //lŠp‚ÆlŠp‚Ì“–‚½‚è”»’è
	bool IsColliderInRange(float circleposx, float circleposy,float Scaffoldposx, float Scaffoldposy,float wihtd , float height);	 //

private://‰~‚Æ‚Ì“–‚½‚è”»’è‚Åg‚¤

	const float range_x = 150;//“–‚½‚è”»’è‚ğæ‚é”ÍˆÍX
	const float range_y = 100;//“–‚½‚è”»’è‚ğæ‚é”ÍˆÍY

	//--------------------------ƒxƒNƒgƒ‹‚È‚Ç‚ÌŒvZ‚ÌŠÖ”--------------------------
	DirectX::XMFLOAT2 RotatePosition(DirectX::XMFLOAT2,float);//‰ñ“]s—ñ
	float dotProduct(DirectX::XMFLOAT2 v1, DirectX::XMFLOAT2 v2);//“àÏ
	//----------------------------------------------------------------------------
};