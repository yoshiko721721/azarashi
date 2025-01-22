#include"SelectScene.h"
#include"../../03_GameMainFile/Application.h"

void SelectScene::Init()
{
	backGround.Init();
}

void SelectScene::Update()
{
	backGround.Update();
	/*if (Input::GetKeyPress(VK_A))
	{
		Application::GetInstance()->ChangeScene(GAMESCENE);
	}*/
}

void SelectScene::Draw()
{
	backGround.Draw();
}

void SelectScene::Uninit()
{
	backGround.Uninit();
}
