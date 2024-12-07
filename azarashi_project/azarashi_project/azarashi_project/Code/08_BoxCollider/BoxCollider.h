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
	DirectX::XMFLOAT2 hitcorners[12] = {//“–‚½‚è”»’è‚ğ‚Æ‚éÛ‚ÌÀ•WŠi”[æ
		{ 0, 0 }, //LeftBottom
		{ 0, 0 }, //RightBottom
		{ 0, 0 }, //RightTop
		{ 0, 0 }, //LeftTop
	};

	bool CheckCollision_Box_Circle(Object* p_player, float Scaffoldposx, float Scaffoldposy, float angle, float wihtd, float height);//lŠp‚Æ‰~‚Ì“–‚½‚è”»’è
	bool CheckCollision_Box_Box(Object* p_player, float Scaffoldposx, float Scaffoldposy, float angle, float wihtd, float height);	 //lŠp‚ÆlŠp‚Ì“–‚½‚è”»’è
	bool IsColliderInRange(float circleposx, float circleposy,float Scaffoldposx, float Scaffoldposy,float wihtd , float height);	 //

private://‰~‚Æ‚Ì“–‚½‚è”»’è‚Åg‚¤

	const float range_x = 50;//“–‚½‚è”»’è‚ğæ‚é”ÍˆÍX
	const float range_y = 100;//“–‚½‚è”»’è‚ğæ‚é”ÍˆÍY

	//--------------------------------ŒvZ‚ÌŠÖ”----------------------------------
	DirectX::XMFLOAT2 RotatePosition(DirectX::XMFLOAT2,float);//‰ñ“]s—ñ
	//----------------------------------------------------------------------------
};