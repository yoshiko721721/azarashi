#pragma once
#include "../../01_Direct3D/BackGround.h"
#include "../../02_Input/input.h"
#include "../../02_Input/miyoshi_input/ControllerInput.h"
#include <vector> 
class WorldUI :public BackGround
{
private:
	const wchar_t* imgname[4] = //上のWorldの表示UIの画像パス
	{
		L"Asset/pic/SelectUI/UI_World1.png",
		L"Asset/pic/SelectUI/UI_World2.png",
		L"Asset/pic/SelectUI/UI_World3.png",
		L"Asset/pic/SelectUI/UI_World4.png"
	};

	//int selectPage = 0; //今なんページなのかどうか
	///std::vector<ID3D11ShaderResourceView*> textures; // テクスチャ情報を格納するベクター
public:
	WorldUI() {}
	~WorldUI() { Uninit(); }
	void Init();
	void Update(int); //更新
};
