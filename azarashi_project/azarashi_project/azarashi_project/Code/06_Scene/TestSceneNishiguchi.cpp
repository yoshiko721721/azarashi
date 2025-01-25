#include"TestSceneNishiguchi.h"

TestSceneNishiguchi::TestSceneNishiguchi(std::vector<ID3D11ShaderResourceView*>& textures) :textures(textures)// , moveGameBlock(2.0f) // 初期化リストを使用してメンバ変数を初期化
{


}

void TestSceneNishiguchi::Init()
{	
	//testFloor.Init();
	//testWall.Init();
	//std::vector<ID3D11ShaderResourceView*> textures(BlockType_MAX); // ベクターを初期化 
    //SVMapLoader csvMapLoader(textures); // textures ベクターを渡して初期化 
	m_MySceneObjects.emplace_back(Application::GetInstance()->AddObject<GameBackGround>());//地形
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
	//csvMapLoader.PrintValueAt(3, 6);
}

void TestSceneNishiguchi::Update()
{
	SDL_Event& e = Controller::Input::e;
	while (SDL_PollEvent(&e) != 0)
	{
		Controller::Input::e = e; // イベントをController::Input::eに設定 
		//testWall.Update();
		//testFloor.Update();
		for (auto& o : m_MySceneObjects)
		{
			o->Update(); // 各オブジェクトの描画メソッドを呼び出
		}

		//p_Player->Update()
	 	//DirectX::XMFLOAT3 pos = Player.GetPos();
		/*for (auto& o : m_MySceneObjects)
		{
			o->Update(); // 各オブジェクトの描画メソッドを呼び出
		}*/
		if (e.type == SDL_CONTROLLERBUTTONDOWN)
		{	
			if (e.cbutton.button == SDL_CONTROLLER_BUTTON_B)
			{
				std::cout << "Xボタンが押されました！" << std::endl;
				Application::GetInstance()->ChangeScene(GAMESCENE);
				return;
			}
		}
	}
}


void TestSceneNishiguchi::Draw()
{
	//testFloor.Draw();
	//testWall.Draw();
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

void TestSceneNishiguchi::Uninit()
{
	testFloor.Uninit();
	testWall.Uninit();
	//pauseText.Uninit();
	// このシーンのオブジェクトを削除する 
	for (auto& o : m_MySceneObjects)
	{
		Application::GetInstance()->DeleteObject(o.get()); // .get()を追加
	}
}

void TestSceneNishiguchi::SetPlayer()
{

}

GamePointer* TestSceneNishiguchi::GetPlayer()
{
	return p_Player;
}