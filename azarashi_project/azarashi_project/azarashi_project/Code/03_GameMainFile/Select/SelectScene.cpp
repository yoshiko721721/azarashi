#include "SelectScene.h"
#include "../../03_GameMainFile/Application.h"

void SelectScene::Init()
{
	backGround.Init();
	worldUI.Init();
	stage1UI.Init();
	stage2UI.Init();
	stage3UI.Init();
	stage4UI.Init();
	cursorL.Init();
	fade.Init();
	sound.Init();
}

void SelectScene::Update()
{
	SDL_Event& e = Controller::Input::e;
	if (!isFading)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			Controller::Input::e = e; // イベントをController::Input::eに設定 
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

				if (e.cbutton.button == SDL_CONTROLLER_BUTTON_RIGHTSHOULDER) //Rボタンで次のワールドに進むよ
				{
					selectPage++;
					if (selectPage > MAX_PAGE)
						selectPage = 0;
					worldUI.Update(selectPage);
					stage1UI.Update(selectPage);
					stage2UI.Update(selectPage);
					stage3UI.Update(selectPage);
					stage4UI.Update(selectPage);
				}

				if (e.cbutton.button == SDL_CONTROLLER_BUTTON_LEFTSHOULDER) //Lボタンで前のワールドに進むよ
				{
					sound.Play(SOUND_LABEL_SE1);
					selectPage--;
					if (selectPage < 0)
						selectPage = 3;
					worldUI.Update(selectPage);
					stage1UI.Update(selectPage);
					stage2UI.Update(selectPage);
					stage3UI.Update(selectPage);
					stage4UI.Update(selectPage);
				}

				int rightStickX = SDL_GameControllerGetAxis(Controller::Input::controller, SDL_CONTROLLER_AXIS_RIGHTX);//右ステックでアザラシちゃんが移動するよ
				if (rightStickX > 32767 / 2)
				{


				}

				/*if (e.cbutton.button == SDL_CONTROLLER_BUTTON_RIGHTSHOULDER)
				{

				}*/
			}
			if (e.type == SDL_JOYAXISMOTION)
			{
				if (e.jaxis.axis == 0)
				{ // X軸
					std::cout << "X Axis: " << e.jaxis.value << std::endl;
				}
				else if (e.jaxis.axis == 1)
				{ // Y軸
					std::cout << "Y Axis: " << e.jaxis.value << std::endl;
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
	backGround.Uninit();
}
