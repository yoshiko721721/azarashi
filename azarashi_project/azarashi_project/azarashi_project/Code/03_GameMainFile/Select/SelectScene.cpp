#include"SelectScene.h"
#include"../../03_GameMainFile/Application.h"

void SelectScene::Init()
{
	//m_MySceneObjects.emplace_back(Game::GetInstance()->AddObject<SelectBackGround>());//�n�`
}

void SelectScene::Update()
{
	if (Input::GetKeyPress(VK_A))
	{
		Application::GetInstance()->ChangeScene(GAMESCENE);
	}
}

void SelectScene::Draw()
{
	backGround.Draw();
}

void SelectScene::Uninit()
{
	backGround.Uninit();
}
