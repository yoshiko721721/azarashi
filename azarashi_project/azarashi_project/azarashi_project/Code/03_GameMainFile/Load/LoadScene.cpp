#include "LoadScene.h"
#include "../../03_GameMainFile/Application.h"

int loadSceneCount = 0;

void LoadScene::Init()
{
	loadSceneCount = 0;
	backGround.Init();
	backGroundpab.Init();
}
void LoadScene::Update()
{
	loadSceneCount++;
	if (loadSceneCount >= 120)
	{
		backGroundpab.Update();
		if(Input::GetButtonTrigger(XINPUT_B) || Input::GetKeyTrigger(VK_RETURN) || Input::GetButtonTrigger(XINPUT_A) || Input::GetButtonTrigger(XINPUT_X) || Input::GetButtonTrigger(XINPUT_Y) || Input::GetButtonTrigger(XINPUT_UP) || Input::GetButtonTrigger(XINPUT_DOWN) || Input::GetButtonTrigger(XINPUT_RIGHT) || Input::GetButtonTrigger(XINPUT_LEFT) || Input::GetButtonTrigger(XINPUT_LEFT_SHOULDER) || Input::GetButtonTrigger(XINPUT_RIGHT_SHOULDER))
		{

			Application::GetInstance()->ChangeScene(STAGESCENE);
		}
	}
}

void LoadScene::Draw()
{
	backGround.Draw();

	if (loadSceneCount >= 120)
	{	
			backGroundpab.Draw();
	}
}
void LoadScene::Uninit()
{

}
