#include "GameScene.h"

void GameScene::Init()
{

	sample.Initialize(L"Asset/pic/MatsuFace_transparent.png");	
	sample.SetSize(100, 100, 0);
	sample.SetPos(300, 0, 0);

	backGround.Init();
	pointer.Init();
	block.Init();

}
void GameScene::Update()
{

	//Eを押した時タイトルシーンに移動
	backGround.Update();
	pointer.Update();
	block.Update();
	
	if (input.GetKeyPress(VK_S)) {
		SetOldScene(GAMESCENE);			//currentScene登録前に
		SetCurrentScene(TITLESCENE);	//oldSceneに自身のシーンタグを登録しないといけない
	}

}
void GameScene::Draw()
{
	sample.Draw();
	backGround.Draw();
	pointer.Draw();
	block.Draw();
}
void GameScene::Uninit()
{
	sample.Uninit();
	backGround.Uninit();
	pointer.Uninit();
	block.Uninit();

}