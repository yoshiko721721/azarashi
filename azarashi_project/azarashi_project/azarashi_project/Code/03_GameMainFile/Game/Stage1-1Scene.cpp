#include "Stage1-1Scene.h" 
#include "../../03_GameMainFile/Application.h" 

Stage1_1Scene::Stage1_1Scene(std::vector<ID3D11ShaderResourceView*>& textures) :textures(textures)// , moveGameBlock(2.0f) // 初期化リストを使用してメンバ変数を初期化
{


}

void Stage1_1Scene::Init()
{
	bool Fopen = csvMapLoader.FileOpen(fileName);
	csvMapLoader.CountRowsAndColumns();
	csvMapLoader.FileClose();
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
	Camera::Lock(p_Player);
}

void Stage1_1Scene::Update()//8,6
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
		if (!pause.isPaused())
		{
			pause.apply();
			backGround.Update();
			for (auto& o : m_MySceneObjects)
			{
				o->Update(); // 各オブジェクトの描画メソッドを呼び出
			}
		}
		else
		{
			//selectPlayer.SetPos(-600, 300, 0);
			DirectX::XMFLOAT3 pos = selectPlayer.GetPos();
			if (Input::GetButtonTrigger(XINPUT_UP) || Input::GetKeyTrigger(VK_UP))
			{
				if (pos.y < 300)
				{
					pos.y += 300;
				}
				//return;
			}
			if (Input::GetButtonTrigger(XINPUT_DOWN) || Input::GetKeyTrigger(VK_DOWN))
			{
				if (pos.y > -300)
				{
					pos.y -= 300;
				}
				//return;
			}
			if (Input::GetButtonTrigger(XINPUT_B) || Input::GetKeyTrigger(VK_RETURN))
			{
				if (pos.y == 300)
				{
					pause.maladaptive();
				}
				else if (pos.y == -300)
				{
					pause.maladaptive();
					Application::GetInstance()->ChangeScene(STAGESCENE);
				}
				else if (pos.y == 0)
				{
					pause.maladaptive();
					Application::GetInstance()->ChangeScene(SELECTSCENE);
					Camera::UnLock();
				}

			}
			selectPlayer.SetPos(pos.x, pos.y, pos.z);
		}
		
	}
}

void Stage1_1Scene::Draw()
{
	backGround.Draw();
	
	//Player.Draw();
	for (auto& o : m_MySceneObjects)
	{
		o->Draw(); // 各オブジェクトの描画メソッドを呼び出
	}

	Test.Draw();

	if (stageExplanation)
	{
		pauseBackGround.Draw();
		stageExplanationUI.Draw();
	}

	if (pause.isPaused())
	{
		selectPlayer.Draw();
		pauseBackGround.Draw();
		pauseUI.Draw();
	}
	

}

void Stage1_1Scene::Uninit()
{
	selectPlayer.Uninit();
	backGround.Uninit();
	stageExplanationUI.Uninit();
	pauseBackGround.Uninit();
	pauseUI.Uninit();
	Test.Uninit();
	//Player.Uninit();
	for (auto& o : m_MySceneObjects)
	{
		Application::GetInstance()->DeleteObject(o.get()); // .get()を追加
	}
	Camera::UnLock();
}