#pragma once
#include "../02_Input/miyoshi_input/ControllerInput.h"
#include "../06_Scene/Scene.h" 
#include "../11_Pause/pause.h"
#include "../10_Timer/Timer.h"
#include "../12_CSVMapLoader/CSVMapLoader.h"
#include "../03_GameMainFile/Game/MoveGameBlock.h"

class TestSceneNishiguchi : public Scene
{
private:
	Object sample;

	Pause pause;
	Timer timer;
	TestFloor testFloor;
	TestWall testWall;
	GamePointer* p_Player;
	vector<GameBlock*> b_Block;
	//PauseText pauseText;
	std::vector<ID3D11ShaderResourceView*>& textures; // textures �������o�ϐ��Ƃ��Đ錾 
	CSVMapLoader csvMapLoader;
	//SceneManager& sceneManager; // sceneManager �������o�ϐ��Ƃ��Đ錾
	SDL_Event e;
	//SDL_GameController* controller = nullptr;

public:
	std::vector<std::unique_ptr<Object>> m_MySceneObjects; // ���̃V�[���̃I�u�W�F�N�g 
	std::string fileName = "Code/12_CSVMapLoader/data.csv"; //�X�e�[�W�T�C�Y
	TestSceneNishiguchi(std::vector<ID3D11ShaderResourceView*>& textures);
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