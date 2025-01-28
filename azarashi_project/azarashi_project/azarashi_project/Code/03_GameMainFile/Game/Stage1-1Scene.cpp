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
	
	backGround.Init();
	stageExplanationUI.Init();
	Camera::Lock(p_Player);
}

void Stage1_1Scene::Update()//8,6
{
	if (stageExplanation)
	{
		if (Input::GetButtonTrigger(XINPUT_B))
		{
			stageExplanation = false;
			//Application::GetInstance()->ChangeScene(GAMESCENE);
			return;
		}
		return;
	}
	else
	{
		backGround.Update();
		for (auto& o : m_MySceneObjects)
		{
			o->Update(); // 各オブジェクトの描画メソッドを呼び出
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
	
	if (stageExplanation)
	{
		stageExplanationUI.Draw();
	}
}

void Stage1_1Scene::Uninit()
{
	backGround.Uninit();
	stageExplanationUI.Uninit();
	//Player.Uninit();
	for (auto& o : m_MySceneObjects)
	{
		Application::GetInstance()->DeleteObject(o.get()); // .get()を追加
	}
	Camera::UnLock();
}