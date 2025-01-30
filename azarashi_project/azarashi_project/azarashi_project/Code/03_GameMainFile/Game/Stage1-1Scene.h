#pragma once
#include "../../02_Input/miyoshi_input/ControllerInput.h"
#include "../../06_Scene/Scene.h" 
#include "../../11_Pause/pause.h"
#include "../../10_Timer/Timer.h"
#include "../../12_CSVMapLoader/CSVMapLoader.h"
#include "../Game/MoveGameBlock.h"
#include "../../07_Camera/Camera.h"
#include "StageExplanation.h"
#include "PauseBackGround.h"
#include "../../11_Pause/PauseUI.h"
#include "../../11_Pause/PauseCursor.h"

class Stage1_1Scene : public Scene
{
private:
	Object sample;

	Pause pause;
	PauseCursor selectPlayer;
	//Timer timer;
	GameBackGround backGround;
	GamePointer* p_Player;
	PauseBackGround pauseBackGround;
	//TestPointer testPointer;
	StageExplanation stageExplanationUI;
	PauseUI pauseUI;
	std::vector<ID3D11ShaderResourceView*>& textures; // textures �������o�ϐ��Ƃ��Đ錾 
	CSVMapLoader csvMapLoader;
	SDL_Event e;
	DirectX::XMFLOAT2 centerPos{0,0};

	bool stageExplanation = true;

public:
	std::vector<std::unique_ptr<Object>> m_MySceneObjects; // ���̃V�[���̃I�u�W�F�N�g 
	std::string fileName = "Code/12_CSVMapLoader/Stage1_1.csv"; //�X�e�[�W�T�C�Y
	Stage1_1Scene(std::vector<ID3D11ShaderResourceView*>& textures);
	void Init(); //������ 
	void Update(); //�X�V 
	void Draw(); //�`�� 
	void Uninit(); //�I��
};
