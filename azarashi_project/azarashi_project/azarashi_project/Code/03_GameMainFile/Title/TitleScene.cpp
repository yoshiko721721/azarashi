#include"TitleScene.h"
#include"../../03_GameMainFile/Application.h"

void TitleScene::Init()
{
	backGround.Init();
}
void TitleScene::Update()
{

	if (Input::GetKeyPress(VK_A)) {
		Application::GetInstance()->ChangeScene(TESTSCENE);
	}


}
void TitleScene::Draw()
{
	backGround.Draw();
}
void TitleScene::Uninit()
{
	backGround.Uninit();
}


