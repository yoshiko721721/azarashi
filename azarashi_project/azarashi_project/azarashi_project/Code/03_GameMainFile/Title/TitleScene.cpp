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
	//sound.Play(SOUND_LABEL_BGM1);
	//sound.Init();
	//sound.Play(SOUND_LABEL_BGM1);
}

void TitleScene::Update()
{
	if (isFirst)
	{
		if (!isFading)
		{
			sound.Stop(SOUND_LABEL_BGM1);
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
				//csound.Play(SOUND_LABEL_BGM1);
			}
			return;
		}
	}
	else
	{
		backGroundpab.Update();

		if (!isFading)
		{

			if (Input::GetButtonTrigger(XINPUT_B))
			{
				sound.Play(SOUND_LABEL_SE1);
				isFading = true;
				fade.SetisFading(isFading);
				fade.SetMode(FADEOUT);
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
				Application::GetInstance()->ChangeScene(SELECTSCENE);
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


