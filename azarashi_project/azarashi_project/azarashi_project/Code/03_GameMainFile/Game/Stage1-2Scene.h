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
#include "../Test/TestPointer.h"
#include "Goal.h"
#include "GameClearUI.h"
#include "GameStartUI.h"
#include "../../13_Effect/FadeEffect.h"
#include "Gimmick/GameGimmickUI.h"
#include "../../09_Sound/sound.h"
#include "GoUI.h"
#include "Menu.h"

class Stage1_2Scene : public Scene
{
private:
	Object sample;
	GameClearUI clearUI;
	GameGimmickUI gimmickUI;
	TestPointer Test;
	GoUI go;
	Menu menu;

	Pause pause;
	FadeEffect fade;
	PauseCursor selectPlayer;
	GameBackGround backGround;
	GamePointer* p_Player;
	PauseBackGround pauseBackGround;
	StageExplanation stageExplanationUI;
	PauseUI pauseUI;
	std::vector<ID3D11ShaderResourceView*>& textures; // textures �������o�ϐ��Ƃ��Đ錾 
	CSVMapLoader csvMapLoader;
	SDL_Event e;
	DirectX::XMFLOAT2 centerPos{ 0,0 };

	bool stageExplanation = true;

	bool isGoalAchieved = false;

	int countStay = 0;//�҂Ƃ���count

public:
	std::vector<std::unique_ptr<Object>> m_MySceneObjects; // ���̃V�[���̃I�u�W�F�N�g 
	std::string fileName = "Code/12_CSVMapLoader/Stage1_2.csv"; //�X�e�[�W�T�C�Y
	Stage1_2Scene(std::vector<ID3D11ShaderResourceView*>& textures);
	void Init(); //������ 
	void Update(); //�X�V 
	void Draw(); //�`�� 
	void Uninit(); //�I��
};

