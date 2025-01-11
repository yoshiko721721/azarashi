#pragma once
#include "../../06_Scene/Scene.h" 
#include "../Game/GameBackGround.h"
#include "../Game/GamePointer.h"
#include "TestWall.h"
#include "Testfloor.h"
#include "../Game/GamePointer.h"
#include "../Game/GameBlock.h"
#include "../../11_Pause/pause.h"
#include "../../10_Timer/Timer.h"
#include "../../12_CSVMapLoader/CSVMapLoader.h"
#include "../Game/MoveGameBlock.h"

class TestStageScene_Nakae : public Scene
{
private:
	Object sample;
	std::vector<std::unique_ptr<Object>> m_MySceneObjects; // ���̃V�[���̃I�u�W�F�N�g 
	Pause pause;
	Timer timer;
	GameBackGround TestBackGround;
	//PauseText pauseText;
	std::vector<ID3D11ShaderResourceView*>& textures; // textures �������o�ϐ��Ƃ��Đ錾 
	MoveGameBlock moveGameBlock;
	CSVMapLoader csvMapLoader;
	//SceneManager& sceneManager; // sceneManager �������o�ϐ��Ƃ��Đ錾

public:
	std::string fileName = "Code/12_CSVLoader/data.csv"; //�X�e�[�W�T�C�Y
	TestStageScene_Nakae(std::vector<ID3D11ShaderResourceView*>& textures);
	//TestStageScene_Nakae():moveGameBlock{ };
	//SelectScene(SceneManager& sceneManager, std::vector<ID3D11ShaderResourceView*>& textures);
	void Init(); //������ 
	void Update(); //�X�V 
	void Draw(); //�`�� 
	void Uninit(); //�I��
	void AddObject();
};

