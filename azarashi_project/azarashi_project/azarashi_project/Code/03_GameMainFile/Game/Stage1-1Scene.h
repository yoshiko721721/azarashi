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
	std::vector<ID3D11ShaderResourceView*>& textures; // textures をメンバ変数として宣言 
	CSVMapLoader csvMapLoader;
	SDL_Event e;
	DirectX::XMFLOAT2 centerPos{0,0};

	bool stageExplanation = true;

public:
	std::vector<std::unique_ptr<Object>> m_MySceneObjects; // このシーンのオブジェクト 
	std::string fileName = "Code/12_CSVMapLoader/Stage1_1.csv"; //ステージサイズ
	Stage1_1Scene(std::vector<ID3D11ShaderResourceView*>& textures);
	void Init(); //初期化 
	void Update(); //更新 
	void Draw(); //描画 
	void Uninit(); //終了
};
