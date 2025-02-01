#pragma once
#include "../../01_Direct3D/BackGround.h"
#include "../../02_Input/input.h"
#include "../../02_Input/miyoshi_input/ControllerInput.h"
#include <vector> 
class Stage4 :public BackGround
{
private:
	//int selectPage = 0; //今なんページなのかどうか
	//ID3D11ShaderResourceView* textures[4]; // テクスチャ情報を格納するベクター
public:
	Stage4() {}
	~Stage4() { Uninit(); }
	void Init();
	void Update(int); //更新
	//ID3D11ShaderResourceView* LoadTexture(const wchar_t*);

};
