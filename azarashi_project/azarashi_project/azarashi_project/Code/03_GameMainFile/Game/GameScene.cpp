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

	//backGround.Update();
	pointer.Update(block.GetAngle());
	block.Update();

	if (Input::GetKeyTrigger(VK_RETURN)) {
		pointer.body.AddForce(10.0f, 0.0f);
	}

	

	//床に当たった時　衝突判定
	if (block.collider.CheckCollision_Box_Circle(&pointer, &block) )
	{
		
		pointer.body.Repulsion(pointer.GetFrictionResistance());			//反発
		pointer.body.VectorPruductAngle(&pointer.body.vector,
										 block.GetAngle(),					//角度に合わせて座標変換
										 pointer.GetFrictionResistance());
		pointer.RotateTexture(block.GetFrictionRasistance());				//横移動と連動した画像の回転

	}





	if (Input::GetKeyTrigger(VK_S)) {
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