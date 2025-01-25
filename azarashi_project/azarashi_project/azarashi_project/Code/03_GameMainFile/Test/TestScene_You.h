#pragma once
#include "../../02_Input/miyoshi_input/ControllerInput.h"
#include "../../06_Scene/Scene.h" 
#include "../../11_Pause/pause.h"
#include "../../10_Timer/Timer.h"
#include "../../12_CSVMapLoader/CSVMapLoader.h"
#include "../Game/MoveGameBlock.h"

class TestScene_You : public Scene
{
private:
	Object sample;
	//GamePointer p_Player;
	std::vector<ID3D11ShaderResourceView*>& textures; // textures をメンバ変数として宣言 
	CSVMapLoader csvMapLoader;
	SDL_Event e;

	GamePointer* p_Player;

public:
	std::vector<std::unique_ptr<Object>> m_MySceneObjects; // このシーンのオブジェクト 
	std::string fileName = "Code/12_CSVMapLoader/data.csv"; //ステージサイズ
	TestScene_You( std::vector<ID3D11ShaderResourceView*>& textures ) ;
	//~TestScene_You() {  }
	void Init();		//初期化
	void Update();		//更新
	void Draw();		//描画
	void Uninit();		//終了

	void SetPlayer ( );
	GamePointer* GetPlayer ( );
};

//extern TestScene_You* testScene_You;
