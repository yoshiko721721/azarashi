#include "SelectScene.h"
#include "../../03_GameMainFile/Application.h"

extern Sound sound;

void SelectScene::Init()
{
	backGround.Init();
	worldUI.Init();
	stage1UI.Init();
	stage2UI.Init();
	stage3UI.Init();
	stage4UI.Init();
	cursorL.Init();
	cursorR.Init();
	selectPlayer.Init();
	fade.Init();
	titleBackUI.Init();
	titleBackUI.Init();
	//sound.Play(SOUND_LABEL_BGM1);
}

void SelectScene::Update()
{
	float alphaR = 0;
	float alphaL = 0;

	//SDL_Event& e = Controller::Input::e;
	if (!isFading)
	{
			//Controller::Input::e = e; // �C�x���g��Controller::Input::e�ɐݒ� 
			backGround.Update();
			cursorR.Update(alphaR);

			if (Input::GetButtonTrigger(XINPUT_B))
			{
				isFading = true;
				fade.SetisFading(isFading);
				fade.SetMode(FADEOUT);
				//Application::GetInstance()->ChangeScene(TESTSCENE);
			}

			if (Input::GetButtonTrigger(XINPUT_RIGHT_SHOULDER))
			{
				sound.Play(SOUND_LABEL_SE1);
				
				if (selectPage < MAX_PAGE)//�y�[�W��MAX�ɂȂ�����
				{
					selectPage++;			//�y�[�W�ړ�
					alphaR = 1.0;
				}

				worldUI.Update(selectPage);
				stage1UI.Update(selectPage);
				stage2UI.Update(selectPage);
				stage3UI.Update(selectPage);
				stage4UI.Update(selectPage);
			}

			if (Input::GetButtonTrigger(XINPUT_LEFT_SHOULDER))
			{
				sound.Play(SOUND_LABEL_SE1);
				if (selectPage > 0)
				{
					selectPage--;
				}
					//selectPage = 3;
				worldUI.Update(selectPage);
				stage1UI.Update(selectPage);
				stage2UI.Update(selectPage);
				stage3UI.Update(selectPage);
				stage4UI.Update(selectPage);
			}

			if (Input::GetButtonTrigger(XINPUT_LEFT))
			{
				sound.Play(SOUND_LABEL_SE2);
				selectStage--;
				if (selectStage < 0)
				{
					selectStage = 3;
				}
						
				selectPlayer.Update(selectStage);
			}

			if (Input::GetButtonTrigger(XINPUT_RIGHT))
			{
				sound.Play(SOUND_LABEL_SE2);
				selectStage++;
				if (selectStage > MAX_PAGE)
				{
					selectStage = 0;
				}
					
				selectPlayer.Update(selectStage);
			}

			if (Input::GetButtonTrigger(XINPUT_UP))
			{
				sound.Play(SOUND_LABEL_SE2);
				selectStage = 4;
				selectPlayer.Update(selectStage);
			}

			if (Input::GetButtonTrigger(XINPUT_DOWN))
			{
				sound.Play(SOUND_LABEL_SE2);
				selectStage = 0;
				selectPlayer.Update(selectStage);
			}

			if (selectPage == 0)
			{
				alphaR = 1.0;
				alphaL = 0.0;
			}
			else if (selectPage == 3)
			{
				alphaR = 0.0;
				alphaL = 1.0;
			}
			else
			{
				alphaR = 1.0;
				alphaL = 1.0;
			}
			cursorL.Update(alphaL);
			cursorR.Update(alphaR);
			//}
			//if (e.type == SDL_JOYAXISMOTION)
			//{
				/*if (e.jaxis.axis == 0)
				{ // X��

				}
				else if (e.jaxis.axis == 1)
				{ // Y��
					
				}*/
			//}
		//}
	}
	else
	{
		isFading = fade.Update(0.08);
		if (isFading == false && fade.GetMode() == FADEOUT && selectStage != 4)
		{
			Application::GetInstance()->ChangeScene(LOADSCENE);
		}

		if (isFading == false && fade.GetMode() == FADEOUT && selectStage == 4)
		{
			Application::GetInstance()->ChangeScene(TITLESCENE);
		}
	}
}

void SelectScene::Draw()
{
	backGround.Draw();
	stage1UI.Draw();
	stage2UI.Draw();
	stage3UI.Draw();
	stage4UI.Draw();
	worldUI.Draw();
	cursorL.Draw();
	cursorR.Draw();
	titleBackUI.Draw();
	selectPlayer.Draw();
	fade.Draw();
}

void SelectScene::Uninit()
{
	fade.Uninit();
	worldUI.Uninit();
	stage1UI.Uninit();
	stage2UI.Uninit();
	stage3UI.Uninit();
	stage4UI.Uninit();
	cursorL.Uninit();
	cursorR.Uninit();
	selectPlayer.Uninit();
	backGround.Uninit();
	titleBackUI.Uninit();
	sound.Stop(SOUND_LABEL_BGM1);
}
