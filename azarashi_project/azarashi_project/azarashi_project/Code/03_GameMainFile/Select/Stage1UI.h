#pragma once
#include "../../01_Direct3D/BackGround.h"
#include "../../02_Input/input.h"
#include "../../02_Input/miyoshi_input/ControllerInput.h"
#include <vector> 
class Stage1UI :public BackGround
{
private:
	const wchar_t* imgname[4] = //上のWorldの表示UIの画像パス
	{
		L"Asset/pic/SelectUI/Stageselect_1_1.png",
		L"Asset/pic/SelectUI/Stageselect_2_1.png",
		L"Asset/pic/SelectUI/Stageselect_3_1.png",
		L"Asset/pic/SelectUI/Stageselect_4_1.png"
	};
	ID3D11ShaderResourceView* textures[4]; // テクスチャ情報を格納するベクター
	//int selectPage = 0; //今なんページなのかどうか
	///std::vector<ID3D11ShaderResourceView*> textures; // テクスチャ情報を格納するベクター
public:
	Stage1UI() {}
	~Stage1UI() { Uninit(); }
	void Init();
	void Update(int); //更新
	ID3D11ShaderResourceView* LoadTexture(const wchar_t*);
};

