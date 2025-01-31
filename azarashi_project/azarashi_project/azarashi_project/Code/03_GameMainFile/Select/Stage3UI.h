#pragma once
#include "../../01_Direct3D/BackGround.h"
#include "../../02_Input/input.h"
#include "../../02_Input/miyoshi_input/ControllerInput.h"
#include <vector> 
class Stage3UI :public BackGround
{
private:
	const wchar_t* imgname[4] = //上のWorldの表示UIの画像パス
	{
		L"Asset/pic/SelectUI/Stageselect_1_3.png",
		L"Asset/pic/SelectUI/Stageselect_2_3.png",
		L"Asset/pic/SelectUI/Stageselect_3_3.png",
		L"Asset/pic/SelectUI/Stageselect_4_3.png"
	};
	ID3D11ShaderResourceView* textures[4]; // テクスチャ情報を格納するベクター
	//int selectPage = 0; //今なんページなのかどうか

public:
	Stage3UI() {}
	~Stage3UI() { Uninit(); }
	void Init();
	void Update(int); //更新
	ID3D11ShaderResourceView* LoadTexture(const wchar_t*);

};


