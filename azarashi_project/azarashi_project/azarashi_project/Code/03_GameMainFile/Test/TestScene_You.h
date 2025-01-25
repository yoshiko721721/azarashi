#pragma once
#include "../../06_Scene/Scene.h"
#include "../../02_Input/miyoshi_input/ControllerInput.h"
#include "../../11_Pause/pause.h"
#include "../../10_Timer/Timer.h"
#include "../../12_CSVMapLoader/CSVMapLoader.h"
#include "../Game/MoveGameBlock.h"

class TestScene_You : public Scene
{
private:
	Object sample;

	Pause pause;
	Timer timer;
	TestFloor testFloor;
	TestWall testWall;
	GamePointer* p_Player;
	std::vector<ID3D11ShaderResourceView*>& textures; // textures をメンバ変数として宣言 
	CSVMapLoader csvMapLoader;
	SDL_Event e;

public:
	TestScene_You(std::vector<ID3D11ShaderResourceView*>& textures);
	std::vector<std::unique_ptr<Object>> m_MySceneObjects; // このシーンのオブジェクト 
	std::string fileName = "Code/12_CSVMapLoader/data.csv"; //ステージサイズ

	~TestScene_You() {  }
	void Init(); //初期化 
	void Update(); //更新 
	void Draw(); //描画 
	void Uninit(); //終了
	GamePointer* GetPlayer();
	void SetPlayer();
	//void AddObject();

};

extern TestScene_You* testScene_You;
