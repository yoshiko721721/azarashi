#include "GameScene.h"
#include "../../08_Collider/BoxCollider.h"


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

	if (Input::GetKeyPress(VK_T)) {
		pointer.SetAzaNum(CIRCLE);
	}
	else {
		pointer.SetAzaNum(STAND);
	}

	//床に当たった時　衝突判定
	if (BoxCollider::ColliderWithCircle(&pointer, &block) )
	{
		if (Input::GetKeyTrigger(VK_RETURN)) {
			pointer.body.AddForce(0.0f, -30.0f);
		}

		//横方向の更新
		pointer.body.HorizonUpdate(&pointer.body.vector,					
									pointer.GetFrictionResistance(),
									block.GetAngle());
		//反発
		pointer.body.Repulsion(pointer.GetFrictionResistance(), block.GetAngle());
		
		pointer.body.DampingVector(pointer.damping , pointer.azaNum);


	}
	
	//横移動と連動した画像の回転
	if (pointer.azaNum == CIRCLE) {
		pointer.RotateTexture(block.GetFrictionRasistance());				
	}

	if (pointer.isChangeMode()) {
		switch (pointer.azaNum) {
			case CIRCLE: pointer.Initialize(AZARASHI_PICTURE_CIRCLE) ; break;
			case STAND : pointer.Initialize(AZARASHI_PICTURE_STAND ) ; 
				pointer.SetAngle(block.GetAngle());
				break;
		}

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