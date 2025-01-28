#pragma once
#include "../../02_Input/miyoshi_input/ControllerInput.h"
#include "../../06_Scene/Scene.h" 
#include "../../11_Pause/pause.h"
#include "../../10_Timer/Timer.h"
#include "../../12_CSVMapLoader/CSVMapLoader.h"
#include "../Game/MoveGameBlock.h"
#include "../../07_Camera/Camera.h"
#include "StageExplanation.h"

class StageScene : public Scene
{
private:
	Object sample;

	Pause pause;
	Timer timer;
	GameBackGround backGround;
	GamePointer* p_Player;
	TestPointer testPointer;
	StageExplanation stageExplanationUI;
	std::vector<ID3D11ShaderResourceView*>& textures; // textures �������o�ϐ��Ƃ��Đ錾 
	CSVMapLoader csvMapLoader;
	SDL_Event e;
	int stageSizeX = 0;	//�X�e�[�W����
	int stageSizeY = 0;	//�X�e�[�W�c�� 

	bool stageExplanation = true;

public:
	std::vector<std::unique_ptr<Object>> m_MySceneObjects; // ���̃V�[���̃I�u�W�F�N�g 
	std::string fileName = "Code/12_CSVMapLoader/test.csv"; //�X�e�[�W�T�C�Y
	StageScene(std::vector<ID3D11ShaderResourceView*>& textures);
	void Init(); //������ 
	void Update(); //�X�V 
	void Draw(); //�`�� 
	void Uninit(); //�I��
};
