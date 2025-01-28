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
	std::vector<ID3D11ShaderResourceView*>& textures; // textures をメンバ変数として宣言 
	CSVMapLoader csvMapLoader;
	SDL_Event e;
	int stageSizeX = 0;	//ステージ横幅
	int stageSizeY = 0;	//ステージ縦幅 

	bool stageExplanation = true;

public:
	std::vector<std::unique_ptr<Object>> m_MySceneObjects; // このシーンのオブジェクト 
	std::string fileName = "Code/12_CSVMapLoader/test.csv"; //ステージサイズ
	StageScene(std::vector<ID3D11ShaderResourceView*>& textures);
	void Init(); //初期化 
	void Update(); //更新 
	void Draw(); //描画 
	void Uninit(); //終了
};
