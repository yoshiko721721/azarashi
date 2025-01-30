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
	if (loadSceneCount >= 120)
	{
		backGroundpab.Update();
		if (Input::GetButtonTrigger(XINPUT_B) || Input::GetKeyTrigger(VK_RETURN)){

			Application::GetInstance()->ChangeScene(STAGESCENE);
		}
	}
}

void LoadScene::Draw()
{
	backGround.Object::Draw();

	if (loadSceneCount >= 120)
	{	
			backGroundpab.Object::Draw();
	}
}
void LoadScene::Uninit()
{

}
