#pragma once
#include "../../01_Direct3D/BackGround.h"
#include "../../02_Input/input.h"
#include "../../02_Input/miyoshi_input/ControllerInput.h"
#include <vector> 
class WorldUI :public BackGround
{
private:
	const wchar_t* imgname[4] = //���World�̕\��UI�̉摜�p�X
	{
		L"Asset/pic/SelectUI/UI_World1.png",
		L"Asset/pic/SelectUI/UI_World2.png",
		L"Asset/pic/SelectUI/UI_World3.png",
		L"Asset/pic/SelectUI/UI_World4.png"
	};

	//int selectPage = 0; //���Ȃ�y�[�W�Ȃ̂��ǂ���
	///std::vector<ID3D11ShaderResourceView*> textures; // �e�N�X�`�������i�[����x�N�^�[
public:
	WorldUI() {}
	~WorldUI() { Uninit(); }
	void Init();
	void Update(int); //�X�V
};
