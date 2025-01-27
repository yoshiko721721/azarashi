#include "LoadScene.h"
#include "../../03_GameMainFile/Application.h"

int loadSceneCount = 0;

void LoadScene::Init()
{
	backGround.Init();
}
void LoadScene::Update()
{
	loadSceneCount++;

	if (loadSceneCount >= 120)
	{
		Application::GetInstance()->ChangeScene(GAMESCENE);
	}

}
void LoadScene::Draw()
{
	backGround.Object::Draw();
}
void LoadScene::Uninit()
{

}
