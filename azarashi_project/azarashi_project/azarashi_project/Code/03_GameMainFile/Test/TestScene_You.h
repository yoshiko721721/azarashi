#pragma once
#include "../../02_Input/miyoshi_input/ControllerInput.h"
#include "../../06_Scene/Scene.h" 
#include "../../11_Pause/pause.h"
#include "../../10_Timer/Timer.h"
#include "../../12_CSVMapLoader/CSVMapLoader.h"
#include "../Game/MoveGameBlock.h"

class TestScene_You : public Scene
{
private:
	Object sample;
	//GamePointer p_Player;
	std::vector<ID3D11ShaderResourceView*>& textures; // textures �������o�ϐ��Ƃ��Đ錾 
	CSVMapLoader csvMapLoader;
	SDL_Event e;

	GamePointer* p_Player;

public:
	std::vector<std::unique_ptr<Object>> m_MySceneObjects; // ���̃V�[���̃I�u�W�F�N�g 
	std::string fileName = "Code/12_CSVMapLoader/data.csv"; //�X�e�[�W�T�C�Y
	TestScene_You( std::vector<ID3D11ShaderResourceView*>& textures ) ;
	//~TestScene_You() {  }
	void Init();		//������
	void Update();		//�X�V
	void Draw();		//�`��
	void Uninit();		//�I��

	void SetPlayer ( );
	GamePointer* GetPlayer ( );
};

//extern TestScene_You* testScene_You;
