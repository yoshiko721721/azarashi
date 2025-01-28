#include "TestStageScene_Nakae.h" 
#include "../../03_GameMainFile/Application.h" 

TestStageScene_Nakae::TestStageScene_Nakae(std::vector<ID3D11ShaderResourceView*>& textures) :textures(textures)// , moveGameBlock(2.0f) // 初期化リストを使用してメンバ変数を初期化
{


}

void TestStageScene_Nakae::Init()
{	
	//m_MySceneObjects.emplace_back(Application::GetInstance()->AddObject<GameBackGround>());//地形
	backGround.Init();
	bool Fopen = csvMapLoader.FileOpen(fileName);
	csvMapLoader.CountRowsAndColumns();
	csvMapLoader.FileClose();
	std::cout << "行数: " << csvMapLoader.rowCount << std::endl; std::cout << "列数: " << csvMapLoader.colCount << std::endl; // データを表示 
	for (const auto& row : csvMapLoader.data)
	{
		for (const auto& value : row)
		{
			std::cout << value << " ";
		}
		std::cout << std::endl;
	}

	csvMapLoader.LoadTextures(); //texturesベクターを渡さずに呼び出し
	p_Player = csvMapLoader.AddObject(&m_MySceneObjects);
	//Player.Init();
	Camera::Lock(p_Player);
}

void TestStageScene_Nakae::Update()
{
	backGround.Update();
	SDL_Event& e = Controller::Input::e;
	for (auto& o : m_MySceneObjects)
	{
			o->Update(); // 各オブジェクトの描画メソッドを呼び出
	}
	if (SDL_PollEvent(&e) != 0)
	{
		Controller::Input::e = e; // イベントをController::Input::eに設定 
		
		//Player.Update();
		if (e.type == SDL_CONTROLLERBUTTONDOWN)
		{	
			if (e.cbutton.button == SDL_CONTROLLER_BUTTON_B)
			{
				Application::GetInstance()->ChangeScene(GAMESCENE);
				return;
			}
		}
	}
}


void TestStageScene_Nakae::Draw()
{
	backGround.Draw();
	for (auto& o : m_MySceneObjects)
	{
		o->Draw(); // 各オブジェクトの描画メソッドを呼び出
	}
	//Player.Draw();
}

void TestStageScene_Nakae::Uninit()
{	
	backGround.Uninit();
	for (auto& o : m_MySceneObjects)
	{
		Application::GetInstance()->DeleteObject(o.get()); // .get()を追加
	}

	Camera::UnLock();
}

void TestStageScene_Nakae::SetPlayer()
{

}

GamePointer* TestStageScene_Nakae::GetPlayer()
{
	return p_Player;
}

/*void TestStageScene_Nakae::AddObject()
{
	int Platformcount = 1;
	int count = 0;
	float x = SCREEN_WIDTH * -1 / 2 + 32;
	float y = SCREEN_HEIGHT / 2 - 32;
	for (int i = 0; i < csvMapLoader.rowCount; i++)
	{
		for (int j = 0; j < csvMapLoader.colCount; j++)
		{
			if (csvMapLoader.data[i][j] == NULLSPACE)
			{
				count++;
			}
			if (csvMapLoader.data[i][j] == FLOOR)
			{
				auto newChip = std::make_unique<GamePointer>(x, y, 100, 100);
				newChip->SetTexture(csvMapLoader.textures[csvMapLoader.data[i][j]]);
				newChip->Init();
				//m_MySceneObjects.push_back(std::move(newChip));
				m_MySceneObjects.emplace_back(Application::GetInstance()->AddObject<GamePointer>());
				count++;

				auto newChip = Application::GetInstance()->AddObject<TestFloor>(x, y, 64, 64);
				newChip->SetTexture(csvMapLoader.textures[csvMapLoader.data[i][j]]);
				newChip->Init();
				m_MySceneObjects.emplace_back(newChip);
				count++;
				//x += 64;
			}
			if (csvMapLoader.data[i][j] == WALL)
			{
				auto newChip = Application::GetInstance()->AddObject<TestWall>(x, y, 64, 64);
				newChip->SetTexture(csvMapLoader.textures[csvMapLoader.data[i][j]]);
				newChip->Init();
				m_MySceneObjects.emplace_back(newChip);
				//x += 64;
			}
			if (csvMapLoader.data[i][j] == PLAYER)
			{
				auto newChip = Application::GetInstance()->AddObject<GamePointer>(x, y, 64, 64);
				newChip->SetTexture(csvMapLoader.textures[csvMapLoader.data[i][j]]);
				newChip->Init();
				m_MySceneObjects.emplace_back(newChip);
			}
			if (csvMapLoader.data[i][j] == INCLINED_PLATFORM)
			{
				//for(csvMapLoader.data[i][j] ==)
				for (int k = 0; j + k >= csvMapLoader.colCount; k++)
				{
					if (csvMapLoader.data[i][j + k] == csvMapLoader.data[i][j])
					{
						Platformcount++;
					}
					else
					{
						auto newChip = Application::GetInstance()->AddObject<InclinedPlatform>(x, y, 64 * Platformcount, 64);
						newChip->SetTexture(csvMapLoader.textures[csvMapLoader.data[i][j]]);
						newChip->Init();
						m_MySceneObjects.emplace_back(newChip);

						break;
					}
				}

			}
			x += 64;
		}
		y -= 64;
		x = SCREEN_WIDTH * -1 / 2 + 32;
	}

}*/