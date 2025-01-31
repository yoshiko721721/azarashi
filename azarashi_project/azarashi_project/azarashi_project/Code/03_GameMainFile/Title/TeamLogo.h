#pragma once
#include "../../01_Direct3D/BackGround.h"
#include "../../01_Direct3D/Object.h"
#include "../../02_Input/input.h"
#include "../../02_Input/miyoshi_input/ControllerInput.h"
#include <vector> 
class TeamLogo :public BackGround
{
private:
	ID3D11ShaderResourceView* textures[4]; // テクスチャ情報を格納するベクター
	//int selectPage = 0; //今なんページなのかどうか
	///std::vector<ID3D11ShaderResourceView*> textures; // テクスチャ情報を格納するベクター
public:
	TeamLogo() {}
	~TeamLogo() { Uninit(); }
	void Init();
	void Update(); //更新
	ID3D11ShaderResourceView* LoadTexture(const wchar_t*);
};