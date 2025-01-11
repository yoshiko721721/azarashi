#pragma once
#include"Scene.h"
#include "../03_GameMainFile/Title/TitleScene.h"
#include "../03_GameMainFile/Game/GameScene.h"


class SceneManager 
{
private:
	std::vector<std::unique_ptr<Scene>> sceneList;
	std::unique_ptr<Scene> currentScene;			//現在のシーン

public:
	// シングルトンパターン
	static SceneManager& GetInstance();

	void AddScene();									//シーン追加
	void ChangeScene(std::unique_ptr<Scene> newScene);	//シーン遷移
	void Update();										//現在のシーンの更新処理
	void Draw();										//現在のシーンの描画処理
	void Uninit();										//現在のシーンの終了処理

	bool isSceneListTogether();							//oldSceneとnowSceneの比較
														//ちがえばture 同じなら false

};

