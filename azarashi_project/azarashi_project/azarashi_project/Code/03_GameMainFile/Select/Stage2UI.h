#pragma once
#include "../../01_Direct3D/Object.h"
#include "../../02_Input/input.h"
#include "../../02_Input/miyoshi_input/ControllerInput.h"
#include <vector> 
class Stage2UI :public Object
{
private:
	const wchar_t* imgname[4] = //���World�̕\��UI�̉摜�p�X
	{
		L"Asset/pic/SelectUI/Stageselect_1_2.png",
		L"Asset/pic/SelectUI/Stageselect_2_2.png",
		L"Asset/pic/SelectUI/Stageselect_3_2.png",
		L"Asset/pic/SelectUI/Stageselect_4_2.png"
	};
	ID3D11ShaderResourceView* textures[4]; // �e�N�X�`�������i�[����x�N�^�[
	//int selectPage = 0; //���Ȃ�y�[�W�Ȃ̂��ǂ���
public:
	Stage2UI() {}
	~Stage2UI() { Uninit(); }
	void Init();
	void Update(int); //�X�V
	ID3D11ShaderResourceView* LoadTexture(const wchar_t*);

};
