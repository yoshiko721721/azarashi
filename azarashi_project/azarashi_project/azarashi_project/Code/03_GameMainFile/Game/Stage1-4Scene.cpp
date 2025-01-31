#include "Stage1-4Scene.h" 
#include "../../03_GameMainFile/Application.h" 

extern Sound sound;

Stage1_4Scene::Stage1_4Scene(std::vector<ID3D11ShaderResourceView*>& textures) :textures(textures)// , moveGameBlock(2.0f) // ���������X�g���g�p���ă����o�ϐ���������
{


}

void Stage1_4Scene::Init()
{
	bool Fopen = csvMapLoader.FileOpen(fileName);
	csvMapLoader.CountRowsAndColumns();	//�s��𐔂���
	csvMapLoader.FileClose();///�t�@�C���Ƃ���
	csvMapLoader.LoadTextures(); //textures�x�N�^�[��n�����ɌĂяo��
	p_Player = csvMapLoader.AddObject(&m_MySceneObjects);
	SDL_GameControllerSetSensorEnabled(Controller::Input::controller, SDL_SENSOR_GYRO, SDL_TRUE);

	backGround.Init();
	stageExplanationUI.Init();
	pauseBackGround.Init();
	pauseUI.Init();
	selectPlayer.Init();
	Test.Init();
	selectPlayer.SetPos(0, 0, 0);
	clearUI.Init();
	gimmickUI.Init();
	//goal.Init();
	sound.Play(SOUND_LABEL_BGM2);
	Camera::Lock(p_Player);
}

void Stage1_4Scene::Update()//8,6
{
	if (stageExplanation)
	{
		if (Input::GetButtonTrigger(XINPUT_B) || Input::GetKeyTrigger(VK_RETURN))
		{
			stageExplanation = false;
			//Application::GetInstance()->ChangeScene(GAMESCENE);
			return;
		}
		return;
	}
	else
	{
		if (isGoalAchieved == false)
		{
			if (!pause.isPaused())
			{
				pause.apply();
				backGround.Update();
				for (auto& o : m_MySceneObjects)
				{
					o->Update(); // �e�I�u�W�F�N�g�̍X�V���\�b�h���Ăяo��

					// o��Object���p������Goal�ł��邩�ǂ������m�F
					if (Goal* goal = dynamic_cast<Goal*>(o.get()))
					{
						// Goal�N���X���L�̏����������ɋL�q
						isGoalAchieved = goal->GetGoal(); // ��: Goal�N���X�̓��ʂȃ��\�b�h���Ăяo��
					}
				}


				//goal.Update();
				//if (goal.GetGoal())
				/*{
					isGoalAchieved = true;
					return;
				}*/ 
			}
			else
			{
				if (Input::GetButtonTrigger(XINPUT_START) || Input::GetKeyTrigger(VK_P))
				{
					pause.maladaptive();
				}

				//selectPlayer.SetPos(-600, 300, 0);
				DirectX::XMFLOAT3 pos = selectPlayer.GetPos();
				if (Input::GetButtonTrigger(XINPUT_UP) || Input::GetKeyTrigger(VK_UP))
				{
					if (pos.y < 250)
					{
						pos.y += 250;
					}
					//return;
				}
				if (Input::GetButtonTrigger(XINPUT_DOWN) || Input::GetKeyTrigger(VK_DOWN))
				{
					if (pos.y > -250)
					{
						pos.y -= 250;
					}
					//return;
				}
				if (Input::GetButtonTrigger(XINPUT_B) || Input::GetKeyTrigger(VK_RETURN))
				{
					if (pos.y == 250)
					{
						pause.maladaptive();
					}
					else if (pos.y == -250)
					{
						pause.maladaptive();
						Application::GetInstance()->ChangeScene(SELECTSCENE);
						Camera::UnLock();
					}
					else if (pos.y == 0)
					{
						pause.maladaptive();
						Application::GetInstance()->ChangeScene(LOADSCENE);
						Camera::UnLock();
					}

				}
				selectPlayer.SetPos(-317, pos.y, pos.z);
			}

		}
		else
		{
			if (countStay == 0)
			{


			}
			countStay++;
			clearUI.Update();
			if (countStay == 120)
			{
				//sound.
				
				fade.SetisFading(true);
				//sound.Play(SOUND_LABEL_SE5);
				fade.SetMode(FADEOUT);
				if (fade.Update(0.06))
				{
					Application::GetInstance()->ChangeScene(SELECTSCENE);
				}
			}

			
		}
		
	}
}

void Stage1_4Scene::Draw()
{
	backGround.Draw();
	
	//Player.Draw();
	for (auto& o : m_MySceneObjects)
	{
		o->Draw(); // �e�I�u�W�F�N�g�̕`�惁�\�b�h���Ăяo
	}
	gimmickUI.Draw();
	Test.Draw();

	if (stageExplanation)
	{
		pauseBackGround.Draw();
		stageExplanationUI.Draw();
	}

	if (pause.isPaused())
	{
		pauseBackGround.Draw();
		pauseUI.Draw();
		selectPlayer.Draw();
	}
	
	if (isGoalAchieved == true)
	{
		clearUI.Draw();
	}
	
	fade.Draw();
}

void Stage1_4Scene::Uninit()
{
	p_Player = nullptr;
	Camera::UnLock();
	fade.Uninit();
	selectPlayer.Uninit();
	backGround.Uninit();
	stageExplanationUI.Uninit();
	pauseBackGround.Uninit();
	pauseUI.Uninit();
	Test.Uninit();
	gimmickUI.Uninit();
	clearUI.Uninit();
	//Player.Uninit();
	for (auto& o : m_MySceneObjects)
	{
		Application::GetInstance()->DeleteObject(o.get()); // .get()��ǉ�
	}
	//Camera::UnLock();
}