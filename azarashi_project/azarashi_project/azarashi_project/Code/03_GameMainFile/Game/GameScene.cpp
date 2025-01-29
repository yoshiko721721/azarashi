#include "GameScene.h"
#include "../../08_Collider/BoxCollider.h"
#include"../../03_GameMainFile/Application.h"


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
	//床に当たった時　衝突判定
	collision = BoxCollider::ColliderWithCircle(&pointer, &block);

	pointer.Update();
	block.Update();

	//横移動と連動した画像の回転
	if (pointer.azaNum == CIRCLE) {
		pointer.RotateTexture();
	}

	if (Input::GetKeyTrigger(VK_S)) {
		Application::GetInstance()->ChangeScene(TITLESCENE);	//ここでoldSceneを入れて置かないと他のシーンで遷移出来ない
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