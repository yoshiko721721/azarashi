#include "LoadScene.h"
#include "../../03_GameMainFile/Application.h"

int loadSceneCount = 0;

void LoadScene::Init()
{
	backGround.Init();
	backGroundpab.Init();
}
void LoadScene::Update()
{
	loadSceneCount++;
	SDL_Event& e = Controller::Input::e;
	if (loadSceneCount >= 120)
	{
		backGroundpab.Update();
		if (e.cbutton.button == SDL_CONTROLLER_BUTTON_B){

			Application::GetInstance()->ChangeScene(GAMESCENE);
		}
	}
}

void LoadScene::Draw()
{
	backGroundpab.Object::Draw();
	backGround.Object::Draw();
}
void LoadScene::Uninit()
{

}
