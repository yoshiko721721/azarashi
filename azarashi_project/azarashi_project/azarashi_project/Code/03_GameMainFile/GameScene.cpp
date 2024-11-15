#include "GameScene.h"

void GameScene::Init()
{

	sample.Init(L"Asset/pic/MatsuFace_transparent.png");	

}
void GameScene::Update()
{
	sample.SetSize(100, 100, 0);
	sample.SetPos(300, 0, 0);

	//Eを押した時タイトルシーンに移動
	if (input.GetKeyPress(VK_S)) {
		SetOldScene(GAMESCENE);			//currentScene登録前に
		SetCurrentScene(TITLESCENE);	//oldSceneに自身のシーンタグを登録しないといけない
	}

}
void GameScene::Draw()
{
	sample.Draw();
}
void GameScene::Uninit()
{
	sample.Uninit();
}