#pragma once
#include "../01_Direct3D/direct3d.h"
#include "../01_Direct3D/Object.h"
#include "../05_WICTextureLoader/WICTextureLoader.h" // テクスチャ読み込みライブラリ

enum Mode			//フェイドモードを列挙
{
	FADEIN ,
	FADEOUT ,
};

class FadeEffect :public Object
{
private:

	Mode fademode;		//フェイドモード

	float fadeInCounter;		//フェイド・インカウント
	float fadeOutCounter;		//フェイド・アウトカウント
	float a;				//透明度変数
	bool isFading;
public:
	/*FadeEffect(Mode Type)
	{
		fademode = Type	
	}*/
	//~Fade ( ) { Uninit ( ); }

	void Init ( );
	bool Update (float);//更新
	void SetMode(Mode changeMode)
	{
		fademode = changeMode;
	}
	void SetisFading(bool changeisFade)
	{
		isFading = changeisFade;
	}

	Mode GetMode()
	{
		return fademode;
	}
};

