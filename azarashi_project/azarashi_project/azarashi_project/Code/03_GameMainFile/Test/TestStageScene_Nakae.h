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
	std::vector<std::unique_ptr<Object>> m_MySceneObjects; // このシーンのオブジェクト 
	Pause pause;
	Timer timer;
	GameBackGround TestBackGround;
	//PauseText pauseText;
	std::vector<ID3D11ShaderResourceView*>& textures; // textures をメンバ変数として宣言 
	MoveGameBlock moveGameBlock;
	CSVMapLoader csvMapLoader;
	//SceneManager& sceneManager; // sceneManager をメンバ変数として宣言

public:
	std::string fileName = "Code/12_CSVLoader/data.csv"; //ステージサイズ
	TestStageScene_Nakae(std::vector<ID3D11ShaderResourceView*>& textures);
	//TestStageScene_Nakae():moveGameBlock{ };
	//SelectScene(SceneManager& sceneManager, std::vector<ID3D11ShaderResourceView*>& textures);
	void Init(); //初期化 
	void Update(); //更新 
	void Draw(); //描画 
	void Uninit(); //終了
	void AddObject();
};

