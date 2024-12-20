#pragma once
#include "../02_Input/input.h"
#include "../06_Scene/SceneManager.h"

class Application {
private:

	SceneManager sceneManager;
public:
	Application();
	void Init(HWND hWnd);	//初期化
	void Update(void);		//更新
	void Draw();			//描画
	void Uninit();			//終了
};
