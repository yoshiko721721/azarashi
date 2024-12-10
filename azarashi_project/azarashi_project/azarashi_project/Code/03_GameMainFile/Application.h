#pragma once
#include "../02_Input/input.h"
#include "../06_Scene/SceneManager.h"

class Application {
private:

	SceneManager sceneManager;
public:
	Application();
	void Init(HWND hWnd);	//‰Šú‰»
	void Update(void);		//XV
	void Draw();			//•`‰æ
	void Uninit();			//I—¹
};
