#pragma once
#include "../../01_Direct3D/BackGround.h"
#include "../../01_Direct3D/Object.h"
#include "../../02_Input/input.h"
#include "../../02_Input/miyoshi_input/ControllerInput.h"
#include <vector> 
class TeamLogo :public BackGround
{
private:
	ID3D11ShaderResourceView* textures[4]; // �e�N�X�`�������i�[����x�N�^�[
	//int selectPage = 0; //���Ȃ�y�[�W�Ȃ̂��ǂ���
	///std::vector<ID3D11ShaderResourceView*> textures; // �e�N�X�`�������i�[����x�N�^�[
public:
	TeamLogo() {}
	~TeamLogo() { Uninit(); }
	void Init();
	void Update(); //�X�V
	ID3D11ShaderResourceView* LoadTexture(const wchar_t*);
};