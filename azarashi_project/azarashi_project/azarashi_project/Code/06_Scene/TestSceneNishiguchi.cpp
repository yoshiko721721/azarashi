#include"TestSceneNishiguchi.h"
#include "../07_Camera/Camera.h"

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

	csvMapLoader.LoadTextures(); //texturesベクターを渡さずに呼び出し
	p_Player = csvMapLoader.AddObject(&m_MySceneObjects);
	b_Block = Application::GetInstance()->GetObjects<GameBlock>();
	for (auto block : b_Block) {
		block->SetPos(1000,0,0);
		block[0].SetPos(0, -400, 0);
		block[0].SetAngle(0);

	}

	//csvMapLoader.PrintValueAt(3, 6);
	Camera::Lock(p_Player);
}

void TestSceneNishiguchi::Update()
{
	SDL_Event& e = Controller::Input::e;
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