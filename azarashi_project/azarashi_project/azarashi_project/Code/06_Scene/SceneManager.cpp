#include "SceneManager.h"
//
//	ポリモーフィズムで使用
//

//シーンの追加
void SceneManager::AddScene()
{
	sceneList.push_back(std::make_unique<TitleScene>());
	sceneList.push_back(std::make_unique<GameScene> ());
}

//シーンの切り替え
void SceneManager::ChangeScene(std::unique_ptr<Scene> newScene)
{
	if (currentScene) {
		currentScene->Uninit();
	}
	
	currentScene = std::move(newScene); //シーンの移動
	currentScene->Init();				// シーンの初期化を行う
	
}

//更新処理
void SceneManager::Update()
{

	if (currentScene)
	{
		//currentScene->input.Update();
		currentScene->Update(); 
	}

	//oldSceneとnewSceneを比較して一致しなかった場合changeSceneをする
	if (isSceneListTogether()) {
		SceneList newBuff = currentScene->GetCurrentScene();
		switch (newBuff) {
		case TITLESCENE: ChangeScene(std::make_unique<TitleScene>());   break;
		case GAMESCENE : ChangeScene(std::make_unique<GameScene>());   break;
		default:  return;
		}
	}

}

//描画処理
void SceneManager::Draw()
{
	D3D_StartRender();
	
	if (currentScene) 
	{
		currentScene->Draw();
	}

	D3D_FinishRender();
}

void SceneManager::Uninit()
{
	if (currentScene) {
		currentScene->Uninit();
	}
}

bool SceneManager::isSceneListTogether()
{
	if (currentScene->GetOldScene() != currentScene->GetCurrentScene()) {
		return true;
	}
	return false;
}

// シングルトンのインスタンス取得
SceneManager& SceneManager::GetInstance() {
	static SceneManager instance;
	return instance;
}
