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
}

void SelectScene::Update()
{
	SDL_Event& e = Controller::Input::e;
	if (!isFading)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			Controller::Input::e = e; // �C�x���g��Controller::Input::e�ɐݒ� 
			backGround.Update();
			if (e.type == SDL_CONTROLLERBUTTONDOWN)
			{
				if (e.cbutton.button == SDL_CONTROLLER_BUTTON_B)
				{
					isFading = true;
					fade.SetisFading(isFading);
					fade.SetMode(FADEOUT);
					//Application::GetInstance()->ChangeScene(TESTSCENE);
				}

				if (e.cbutton.button == SDL_CONTROLLER_BUTTON_RIGHTSHOULDER) //R�{�^���Ŏ��̃��[���h�ɐi�ނ�
				{
					sound.Play(SOUND_LABEL_SE1);
					selectPage++;
					if (selectPage > MAX_PAGE)
					{
						selectPage  = 0;
						selectStage = 1;
						selectPlayer.Update(selectStage);
					}
						
					worldUI.Update(selectPage);
					stage1UI.Update(selectPage);
					stage2UI.Update(selectPage);
					stage3UI.Update(selectPage);
					stage4UI.Update(selectPage);
				}

				if (e.cbutton.button == SDL_CONTROLLER_BUTTON_LEFTSHOULDER) //L�{�^���őO�̃��[���h�ɐi�ނ�
				{
					sound.Play(SOUND_LABEL_SE1);
					selectPage--;
					if (selectPage < 0)
					{
						selectPage  = 3;
						selectStage = 4;
						selectPlayer.Update(selectStage);
					}
						//selectPage = 3;
					worldUI.Update(selectPage);
					stage1UI.Update(selectPage);
					stage2UI.Update(selectPage);
					stage3UI.Update(selectPage);
					stage4UI.Update(selectPage);
				}

				if (e.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_LEFT) //L�{�^���őO�̃��[���h�ɐi�ނ�
				{
					sound.Play(SOUND_LABEL_SE2);
					selectStage--;
					if (selectStage < 0)
					{
						selectStage = 3;
					}
						
					selectPlayer.Update(selectStage);
				}

				if (e.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_RIGHT) //L�{�^���őO�̃��[���h�ɐi�ނ�
				{
					sound.Play(SOUND_LABEL_SE2);
					selectStage++;
					if (selectStage > MAX_PAGE)
					{
						selectStage = 0;
					}
						
					selectPlayer.Update(selectStage);
				}

				//int rightStickX = SDL_GameControllerGetAxis(Controller::Input::controller, SDL_CONTROLLER_AXIS_RIGHTX);//
				/*if (e.cbutton.button == SDL_CONTROLLER_BUTTON_RIGHTSHOULDER)
				{

				}*/
			}
			if (e.type == SDL_JOYAXISMOTION)
			{
				if (e.jaxis.axis == 0)
				{ // X��

				}
				else if (e.jaxis.axis == 1)
				{ // Y��
					
				}
			}
		}
	}
	else
	{
		isFading = fade.Update(0.08);
		if (isFading == false && fade.GetMode() == FADEOUT)
		{
			Application::GetInstance()->ChangeScene(TESTSCENE);
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
}
