#include"TitleScene.h"
#include"../../03_GameMainFile/Application.h"

extern Sound sound;

int teamLogoCount = 0;

void TitleScene::Init()
{
	backGroundpab.Init();
	backGround.Init();
	titleLogo.Init();
	teamLogo.Init();
	fade.Init();
	//sound.Init();
	//sound.Play(SOUND_LABEL_BGM1);
}

void TitleScene::Update()
{
	input.Update();

	if (isFirst)
	{
		if (!isFading)
		{
			teamLogoCount++;
			if(teamLogoCount == 90)
			{
				isFading = true;
				fade.SetisFading(isFading);
				fade.SetMode(FADEOUT);
			}
			return;
		}
		else
		{
			isFading = fade.Update(0.06);
			if (isFading == false && fade.GetMode() == FADEOUT)
			{
				fade.SetMode(FADEIN);
				isFirst = false;
				isFading = true;
				fade.SetisFading(isFading);
				sound.Play(SOUND_LABEL_BGM1);
			}
			return;
		}
	}
	else
	{
		backGroundpab.Update();
		if (Controller::Input::GetKeyTrigger(VK_RETURN))
		{
			sound.Play(SOUND_LABEL_SE1);
			isFading = true;
			fade.SetisFading(isFading);
			fade.SetMode(FADEOUT);

		}
		if (!isFading)
		{
			SDL_Event& e = Controller::Input::e;
			while (SDL_PollEvent(&e) != 0)
			{
				Controller::Input::e = e; // ƒCƒxƒ“ƒg‚ðController::Input::e‚ÉÝ’è
				if (e.type == SDL_CONTROLLERBUTTONDOWN)
				{
					if (e.cbutton.button == SDL_CONTROLLER_BUTTON_B || Controller::Input::GetKeyTrigger(VK_B))
					{
						sound.Play(SOUND_LABEL_SE1);
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
			isFading = fade.Update(0.06);
			if (!isFading)
			{

			}
			if (isFading == false && fade.GetMode() == FADEOUT)
			{
				Application::GetInstance()->ChangeScene(TESTSCENE);
			}

		}
	}
}

void TitleScene::Draw()
{
	if (isFirst)
	{
		teamLogo.Draw();
	}
	if (!isFirst)
	{
		backGround.Draw();
		backGroundpab.Draw();
		titleLogo.Draw();
	}
	fade.Draw();
}

void TitleScene::Uninit()
{
	backGroundpab.Uninit();
	backGround.Uninit();
	titleLogo.Uninit();
	fade.Uninit();
	sound.Stop(SOUND_LABEL_BGM1);
}


