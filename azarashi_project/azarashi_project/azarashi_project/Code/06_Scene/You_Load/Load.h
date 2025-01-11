#pragma once
#include"../../01_Direct3D/direct3d.h"
#include "../../01_Direct3D/Object.h"
#include "../../05_WICTextureLoader/WICTextureLoader.h" // テクスチャ読み込みライブラリ
#include "../../02_Input/input.h"
#include "random"

class Load :public Object
{
private:
	Input input;		//インプット

	float loadCounter;		//ロードカウンター
	bool isLoading = false;	//ローディングフラグ
	int scene = 0;		//シーン変数、一応設定しますが、後にsceneのやつと統合します
	int nextscene = 0;	//次に読み込むシーンの値
public:
	//Load ( ) {}
	//~Load ( ) { Uninit ( ); }

	void Init ( );
	void Update ( );//更新

};
