#include <time.h>
#include <math.h>
#include "Application.h"
#include "../01_Direct3D\Object.h"




Application::Application()
{
}

void Application::Init(HWND hWnd)
{

	D3D_Create(hWnd);							//DirectXを初期化
	srand((unsigned)time(NULL));
	//初期シーンをセット
	sceneManager.ChangeScene(std::make_unique<TitleScene>());
}

void Application::Update(void)
{
	Input::Update();
	sceneManager.Update();
}

void Application::Draw(void) {
	D3D_StartRender();		//描画開始

	sceneManager.Draw();

	D3D_FinishRender();		//描画終了
}

void Application::Uninit(void)
{

	sceneManager.Uninit();

	D3D_Release();			//DirectXを終了
}