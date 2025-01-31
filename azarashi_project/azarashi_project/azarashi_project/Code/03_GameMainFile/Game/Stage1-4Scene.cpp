#include "Stage1-4Scene.h" 
#include "../../03_GameMainFile/Application.h" 

extern Sound sound;

Stage1_4Scene::Stage1_4Scene(std::vector<ID3D11ShaderResourceView*>& textures) :textures(textures)// , moveGameBlock(2.0f) // 初期化リストを使用してメンバ変数を初期化
{


}

void Stage1_4Scene::Init()
{
	bool Fopen = csvMapLoader.FileOpen(fileName);
	csvMapLoader.CountRowsAndColumns();	//行列を数える
	csvMapLoader.FileClose();///ファイルとじる
	csvMapLoader.LoadTextures(); //texturesベクターを渡さずに呼び出し
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
					o->Update(); // 各オブジェクトの更新メソッドを呼び出し

					// oがObjectを継承したGoalであるかどうかを確認
					if (Goal* goal = dynamic_cast<Goal*>(o.get()))
					{
						// Goalクラス特有の処理をここに記述
						isGoalAchieved = goal->GetGoal(); // 例: Goalクラスの特別なメソッドを呼び出し
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
		o->Draw(); // 各オブジェクトの描画メソッドを呼び出
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
		Application::GetInstance()->DeleteObject(o.get()); // .get()を追加
	}
	//Camera::UnLock();
}