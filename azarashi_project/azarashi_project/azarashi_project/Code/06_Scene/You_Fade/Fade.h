#pragma once
#include"../../../01_Direct3D/direct3d.h"
#include "../../../01_Direct3D/Object.h"
#include "../../../05_WICTextureLoader/WICTextureLoader.h" // テクスチャ読み込みライブラリ

class Fade :public Object
{
private:
	enum Mode			//フェイドモードを列挙
	{
		FadeIn ,
		FadeOut ,
	};

	Mode fademode;		//フェイドモード

	float fadeInCounter;		//フェイド・インカウント
	float fadeOutCounter;		//フェイド・アウトカウント

	float a;				//透明度変数
public:
	//Fade ( ) {}
	//~Fade ( ) { Uninit ( ); }

	void Init ( );
	void Update ( );//更新
};

