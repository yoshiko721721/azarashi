#include"TestScene_You.h"
#include"../../03_GameMainFile/Application.h"




TestScene_You::TestScene_You ( std::vector<ID3D11ShaderResourceView*>& textures ) :textures ( textures )
{

}

void TestScene_You::Init()
{
	m_MySceneObjects.emplace_back ( Application::GetInstance ( )->AddObject<GameBackGround> ( ) );//地形
	bool Fopen = csvMapLoader.FileOpen ( fileName );
	csvMapLoader.CountRowsAndColumns ( );
	csvMapLoader.FileClose ( );
	std::cout << "行数: " << csvMapLoader.rowCount << std::endl; std::cout << "列数: " << csvMapLoader.colCount << std::endl; // データを表示 
	for ( const auto& row : csvMapLoader.data )
	{
		for ( const auto& value : row )
		{
			std::cout << value << " ";
		}
		std::cout << std::endl;
	}

	csvMapLoader.LoadTextures ( ); //texturesベクターを渡さずに呼び出し
	p_Player = csvMapLoader.AddObject ( &m_MySceneObjects );
	//csvMapLoader.PrintValueAt(3, 6);
}
void TestScene_You::Update()
{
	SDL_Event& e = Controller::Input::e;
	while ( SDL_PollEvent ( &e ) != 0 )
	{
		Controller::Input::e = e; // イベントをController::Input::eに設定 
		//testWall.Update();
		//testFloor.Update();

		for ( auto& o : m_MySceneObjects )
		{
			o->Update ( ); // 各オブジェクトの描画メソッドを呼び出
		}
		

		//p_Player->Update ( );
		//DirectX::XMFLOAT3 pos = Player.GetPos();
		/*for (auto& o : m_MySceneObjects)
		{
			o->Update(); // 各オブジェクトの描画メソッドを呼び出
		}*/
		if ( e.type == SDL_CONTROLLERBUTTONDOWN )
		{
			if ( e.cbutton.button == SDL_CONTROLLER_BUTTON_B )
			{
				std::cout << "Xボタンが押されました！" << std::endl;
				Application::GetInstance ( )->ChangeScene ( GAMESCENE );
				return;
			}
		}
	}

}
void TestScene_You::Draw()
{
	//p_Player->Draw ( );
	for ( auto& o : m_MySceneObjects )
	{
		o->Draw ( ); // 各オブジェクトの描画メソッドを呼び出
	}
}
void TestScene_You::Uninit()
{
	//p_Player->Uninit ( );
	for ( auto& o : m_MySceneObjects )
	{
		Application::GetInstance ( )->DeleteObject ( o.get ( ) ); // .get()を追加
	}
}

void TestScene_You::SetPlayer ( )
{

}

GamePointer* TestScene_You::GetPlayer ( )
{
	return p_Player;
}