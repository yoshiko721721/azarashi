#include "Stage1-1Scene.h" 
#include "../../03_GameMainFile/Application.h" 


Stage1_1Scene::Stage1_1Scene(std::vector<ID3D11ShaderResourceView*>& textures) :textures(textures)// , moveGameBlock(2.0f) // 初期化リストを使用してメンバ変数を初期化
{


}

void Stage1_1Scene::Init()
{
	//bool Fopen = csvMapLoader.FileOpen(fileName);
	//csvMapLoader.CountRowsAndColumns();
	//csvMapLoader.FileClose();
	csvMapLoader.LoadTextures(); //texturesベクターを渡さずに呼び出し
	//p_Player = csvMapLoader.AddObject(&m_MySceneObjects);

	TestFloor* Floor1 = Application::GetInstance()->AddObject<TestFloor>(0, -576, 1408, BLOCKSIZE,0,0);
	Floor1->SetTexture(csvMapLoader.textures[FLOOR]);//textureをセット
	Floor1->Init();//初期化
	m_MySceneObjects.emplace_back(Floor1);

	TestWall* Wall1 = Application::GetInstance()->AddObject<TestWall>(-640, 64,BLOCKSIZE, 1152,0,0);//傾く床を生成
	Wall1->SetTexture(csvMapLoader.textures[WALL]);//textureをセット
	Wall1->Init();//初期化
	m_MySceneObjects.emplace_back(Wall1);

	TestWall* Wall2 = Application::GetInstance()->AddObject<TestWall>(640, 64, BLOCKSIZE, 1152,0,0);//傾く床を生成
	Wall2->SetTexture(csvMapLoader.textures[WALL]);//textureをセット
	Wall2->Init();//初期化
	m_MySceneObjects.emplace_back(Wall2);

	GameBlock* inClinedPlatform = Application::GetInstance()->AddObject<GameBlock>(192, -256, 384, BLOCKSIZE);//傾く床を生成
	inClinedPlatform->SetTexture(csvMapLoader.textures[WALL]);//textureをセット
	inClinedPlatform->Init();//初期化
	m_MySceneObjects.emplace_back(inClinedPlatform);

	GamePointer* Player = Application::GetInstance()->AddObject<GamePointer>(0, -448, BLOCKSIZE, BLOCKSIZE);//プレイヤーを生成
	Player->SetTexture(csvMapLoader.textures[PLAYER]);//textureをセット
	Player->Init();//初期化
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
				o->Update(); // 各オブジェクトの描画メソッドを呼び出
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
		o->Draw(); // 各オブジェクトの描画メソッドを呼び出
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
		Application::GetInstance()->DeleteObject(o.get()); // .get()を追加
	}
	Camera::UnLock();
}