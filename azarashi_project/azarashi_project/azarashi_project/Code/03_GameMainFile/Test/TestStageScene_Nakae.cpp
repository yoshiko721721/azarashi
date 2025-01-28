#include "TestStageScene_Nakae.h" 
#include "../../03_GameMainFile/Application.h" 

TestStageScene_Nakae::TestStageScene_Nakae(std::vector<ID3D11ShaderResourceView*>& textures) :textures(textures)// , moveGameBlock(2.0f) // ���������X�g���g�p���ă����o�ϐ���������
{


}

void TestStageScene_Nakae::Init()
{	
	//m_MySceneObjects.emplace_back(Application::GetInstance()->AddObject<GameBackGround>());//�n�`
	backGround.Init();
	bool Fopen = csvMapLoader.FileOpen(fileName);
	csvMapLoader.CountRowsAndColumns();
	csvMapLoader.FileClose();
	std::cout << "�s��: " << csvMapLoader.rowCount << std::endl; std::cout << "��: " << csvMapLoader.colCount << std::endl; // �f�[�^��\�� 
	for (const auto& row : csvMapLoader.data)
	{
		for (const auto& value : row)
		{
			std::cout << value << " ";
		}
		std::cout << std::endl;
	}

	csvMapLoader.LoadTextures(); //textures�x�N�^�[��n�����ɌĂяo��
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
			o->Update(); // �e�I�u�W�F�N�g�̕`�惁�\�b�h���Ăяo
	}
	if (SDL_PollEvent(&e) != 0)
	{
		Controller::Input::e = e; // �C�x���g��Controller::Input::e�ɐݒ� 
		
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
		o->Draw(); // �e�I�u�W�F�N�g�̕`�惁�\�b�h���Ăяo
	}
	//Player.Draw();
}

void TestStageScene_Nakae::Uninit()
{	
	backGround.Uninit();
	for (auto& o : m_MySceneObjects)
	{
		Application::GetInstance()->DeleteObject(o.get()); // .get()��ǉ�
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