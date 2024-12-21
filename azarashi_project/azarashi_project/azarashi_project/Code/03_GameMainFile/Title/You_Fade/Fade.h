#pragma once
#include"direct3d.h"
#include "../../01_Direct3D/Object.h"
#include "WICTextureLoader.h" // テクスチャ読み込みライブラリ

class Fade :public Object
{
private:
	enum Mode
	{
		FadeIn ,
		FadeOut ,
	};

	Mode fademode;

	float fadeInCounter;
	float fadeOutCounter;
	float r;
	float g;
	float b;
	float a;
public:
	//Fade ( ) {}
	//~Fade ( ) { Uninit ( ); }

	void Init ( );
	void Update ( );//更新
};

