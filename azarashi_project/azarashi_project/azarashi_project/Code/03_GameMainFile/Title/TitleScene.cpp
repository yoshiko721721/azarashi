#include"TitleScene.h"
#include"../../03_GameMainFile/Application.h"

void TitleScene::Init()
{
	backGroundpab.Init();
	backGround.Init();
	titleLogo.Init();
	fade.Init();
	//sound.Init();
	//sound.Play(SOUND_LABEL_BGM1);
}

void TitleScene::Update()
{
	SDL_Event& e = Controller::Input::e;
	if (!isFading)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			Controller::Input::e = e; // イベントをController::Input::eに設定 
			backGroundpab.Update();
			if (e.type == SDL_CONTROLLERBUTTONDOWN)
			{
				if (e.cbutton.button == SDL_CONTROLLER_BUTTON_B)
				{
					isFading = true;
					fade.SetisFading(isFading);
					fade.SetMode(FADEOUT);
					//Application::GetInstance()->ChangeScene(TESTSCENE);
				}
			}
		}
	}
	else
	{
		isFading = fade.Update(0.08);
		if (isFading == false && fade.GetMode() == FADEOUT)
		{
			Application::GetInstance()->ChangeScene(SELECTSCENE);
		}

	}
}

void TitleScene::Draw()
{
	backGround.Draw();
	backGroundpab.Draw();
	titleLogo.Draw();
	fade.Draw();
}

void TitleScene::Uninit()
{
	backGroundpab.Uninit();
	backGround.Uninit();
	titleLogo.Uninit();
	fade.Uninit();
	//sound.Stop(SOUND_LABEL_BGM1);
}


