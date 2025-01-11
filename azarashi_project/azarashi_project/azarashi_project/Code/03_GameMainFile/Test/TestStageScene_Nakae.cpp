#include "TestStageScene_Nakae.h" 
#include "../../03_GameMainFile/Application.h" 

TestStageScene_Nakae::TestStageScene_Nakae(std::vector<ID3D11ShaderResourceView*>& textures) :textures(textures) , moveGameBlock(2.0f) // 初期化リストを使用してメンバ変数を初期化
{


}

void TestStageScene_Nakae::Init()
{
	moveGameBlock.Init();
	testWall.Init();
	/*//std::vector<ID3D11ShaderResourceView*> textures(BlockType_MAX); // ベクターを初期化 
   //SVMapLoader csvMapLoader(textures); // textures ベクターを渡して初期化 
	TestBackGround.Init();
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

	csvMapLoader.LoadTextures(); // textures ベクターを渡さずに呼び出し

	AddObject();
	//int kakunin = csvMapLoader.PrintValueAt(3, 6);

	//timer.Init();
	//pauseText.Init();

	for (auto& o : m_MySceneObjects)
	{
		// 各オブジェクトの描画メソッドを呼び出す
	}*/
}

void TestStageScene_Nakae::Update()
{
	moveGameBlock.Update();
	testWall.Init();
	/*if (pause.isPaused() == false)
	{
		pause.apply();

		if (Input::GetKeyPress(VK_SPACE))
		{

		}

		if (Input::GetKeyPress(VK_S))
		{
			Application::GetInstance()->ChangeScene(GAMESCENE);
		}

		for (auto& o : m_MySceneObjects)
		{
			o->Update(); // 各オブジェクトのUpdateメソッドを呼び出す
		}

	}
	else
	{
		pause.maladaptive();
		return;
	}*/
}

void TestStageScene_Nakae::Draw()
{
	testWall.Init();
	moveGameBlock.Draw();
	/*TestBackGround.Draw();
	for (auto& o : m_MySceneObjects)
	{
		o->Draw(); // 各オブジェクトの描画メソッドを呼び出
	}
	/*if (pause.isPaused() == true)
	{
		pauseText.Draw();
	}*/

	//timer.Draw();*/
}

void TestStageScene_Nakae::Uninit()
{
	testWall.Init();
	moveGameBlock.Uninit();
	//TestBackGround.Uninit();
	//pauseText.Uninit();
	// このシーンのオブジェクトを削除する 
	/*for (auto& o : m_MySceneObjects)
	{
		Application::GetInstance()->DeleteObject(o.get()); // .get()を追加
	}*/
}

void TestStageScene_Nakae::AddObject()
{
	/*int Platformcount = 1;
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
				/*auto newChip = std::make_unique<GamePointer>(x, y, 100, 100);
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
	}*/

}