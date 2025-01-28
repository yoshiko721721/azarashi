#pragma once
#include "../../02_Input/miyoshi_input/ControllerInput.h"
#include "../../06_Scene/Scene.h" 
#include "../../11_Pause/pause.h"
#include "../../10_Timer/Timer.h"
#include "../../12_CSVMapLoader/CSVMapLoader.h"
#include "../Game/MoveGameBlock.h"
#include "../../07_Camera/Camera.h"

class TestStageScene_Nakae : public Scene
{
private:
	Object sample;
	
	Pause pause;
	Timer timer;
	GameBackGround backGround;
	//Floor testFloor;
	//Wall testWall;
	GamePointer* p_Player;
	//GamePointer Player;
	//PauseText pauseText;
	std::vector<ID3D11ShaderResourceView*>& textures; // textures �������o�ϐ��Ƃ��Đ錾 
	CSVMapLoader csvMapLoader;
	//SceneManager& sceneManager; // sceneManager �������o�ϐ��Ƃ��Đ錾
	SDL_Event e;
	//SDL_GameController* controller = nullptr;
	int stageSizeX = 0;	//�X�e�[�W����
	int stageSizeY = 0;	//�X�e�[�W�c�� 

public:
	std::vector<std::unique_ptr<Object>> m_MySceneObjects; // ���̃V�[���̃I�u�W�F�N�g 
	std::string fileName = "Code/12_CSVMapLoader/test.csv"; //�X�e�[�W�T�C�Y
	TestStageScene_Nakae(std::vector<ID3D11ShaderResourceView*>& textures);
	//TestStageScene_Nakae():moveGameBlock{ };
	//SelectScene(SceneManager& sceneManager, std::vector<ID3D11ShaderResourceView*>& textures);
	void Init(); //������ 
	void Update(); //�X�V 
	void Draw(); //�`�� 
	void Uninit(); //�I��
	GamePointer* GetPlayer();
	void SetPlayer();
	//void AddObject();
};

