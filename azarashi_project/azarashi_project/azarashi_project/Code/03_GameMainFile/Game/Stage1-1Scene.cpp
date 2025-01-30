#include "Stage1-1Scene.h" 
#include "../../03_GameMainFile/Application.h" 


Stage1_1Scene::Stage1_1Scene(std::vector<ID3D11ShaderResourceView*>& textures) :textures(textures)// , moveGameBlock(2.0f) // ���������X�g���g�p���ă����o�ϐ���������
{


}

void Stage1_1Scene::Init()
{
	//bool Fopen = csvMapLoader.FileOpen(fileName);
	//csvMapLoader.CountRowsAndColumns();
	//csvMapLoader.FileClose();
	csvMapLoader.LoadTextures(); //textures�x�N�^�[��n�����ɌĂяo��
	//p_Player = csvMapLoader.AddObject(&m_MySceneObjects);

	TestFloor* Floor1 = Application::GetInstance()->AddObject<TestFloor>(0, -576, 1408, BLOCKSIZE,0,0);
	Floor1->SetTexture(csvMapLoader.textures[FLOOR]);//texture���Z�b�g
	Floor1->Init();//������
	m_MySceneObjects.emplace_back(Floor1);

	TestWall* Wall1 = Application::GetInstance()->AddObject<TestWall>(-640, 64,BLOCKSIZE, 1152,0,0);//�X�����𐶐�
	Wall1->SetTexture(csvMapLoader.textures[WALL]);//texture���Z�b�g
	Wall1->Init();//������
	m_MySceneObjects.emplace_back(Wall1);

	TestWall* Wall2 = Application::GetInstance()->AddObject<TestWall>(640, 64, BLOCKSIZE, 1152,0,0);//�X�����𐶐�
	Wall2->SetTexture(csvMapLoader.textures[WALL]);//texture���Z�b�g
	Wall2->Init();//������
	m_MySceneObjects.emplace_back(Wall2);

	GameBlock* inClinedPlatform = Application::GetInstance()->AddObject<GameBlock>(192, -256, 384, BLOCKSIZE);//�X�����𐶐�
	inClinedPlatform->SetTexture(csvMapLoader.textures[WALL]);//texture���Z�b�g
	inClinedPlatform->Init();//������
	m_MySceneObjects.emplace_back(inClinedPlatform);

	GamePointer* Player = Application::GetInstance()->AddObject<GamePointer>(0, -448, BLOCKSIZE, BLOCKSIZE);//�v���C���[�𐶐�
	Player->SetTexture(csvMapLoader.textures[PLAYER]);//texture���Z�b�g
	Player->Init();//������
	p_Player = Player;
	m_MySceneObjects.emplace_back(Player);

	backGround.Init();
	stageExplanationUI.Init();
	pauseCursor.Init();
	pauseBackGround.Init();
	pauseUI.Init();
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
			backGround.Update();
			for (auto& o : m_MySceneObjects)
			{
				o->Update(); // �e�I�u�W�F�N�g�̕`�惁�\�b�h���Ăяo
			}
			pause.apply();
		}
		else
		{
			pauseCursor.Update(pause.isPaused());
			if (Input::GetButtonTrigger(XINPUT_B) || Input::GetKeyTrigger(VK_K))
			{
				pause.maladaptive();
			}
		}
		
		/*if (Input::GetButtonTrigger(XINPUT_B))
		{
			Application::GetInstance()->ChangeScene(GAMESCENE);
			return;
		}*/
	}
}

void Stage1_1Scene::Draw()
{
	backGround.Draw();
	//Player.Draw();
	for (auto& o : m_MySceneObjects)
	{
		o->Draw(); // �e�I�u�W�F�N�g�̕`�惁�\�b�h���Ăяo
	}

	if (pause.isPaused())
	{
		pauseBackGround.Draw();
		pauseCursor.Draw();
		pauseUI.Draw();
	}
	
	if (stageExplanation)
	{
		pauseBackGround.Draw();
		stageExplanationUI.Draw();
	}
}

void Stage1_1Scene::Uninit()
{
	backGround.Uninit();
	stageExplanationUI.Uninit();
	pauseCursor.Uninit();
	pauseBackGround.Uninit();
	pauseUI.Uninit();
	for (auto& o : m_MySceneObjects)
	{
		Application::GetInstance()->DeleteObject(o.get()); // .get()��ǉ�
	}
	Camera::UnLock();
}