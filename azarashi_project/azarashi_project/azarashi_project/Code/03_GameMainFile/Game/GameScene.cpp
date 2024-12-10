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
	pointer.Update();
	block.Update();

	if (Input::GetKeyTrigger(VK_RETURN)) {
		pointer.body.AddForce(10.0f, 0.0f);
	}

	

	//°‚É“–‚½‚Á‚½Žž
	if (pointer.GetPos().x >= block.GetPos().x - block.GetSize().x / 2 &&
		pointer.GetPos().x <= block.GetPos().x + block.GetSize().x / 2 &&
		pointer.GetPos().y <= block.GetPos().y + block.GetSize().y / 2 )
	{

		pointer.body.Repulsion(pointer.GetFrictionResistance());		//”½”­
		pointer.body.HorizonUpdate(&pointer.body.vector,				//
									pointer.GetFrictionResistance(),
									block.GetAngle());

		//’n–Ê‚Ìã‚ÉˆÊ’u‚ðC³
		pointer.SetPos(pointer.GetPos().x, block.GetPos().y + pointer.GetCircleRadius() + 23, 0);
		pointer.body.VectorPruductAngle(&pointer.body.vector,
			block.GetAngle(),
			pointer.GetFrictionResistance());


		pointer.RotateTexture(block.GetFrictionRasistance());

	}


	//if (pointer.GetPos().x >= block.GetPos().x   - block.GetSize().x / 2 &&
	//	pointer.GetPos().x <= block.GetPos().x   + block.GetSize().x / 2 &&
	//	pointer.GetPos().y <= pointer.GetPos().y + block.GetSize().y + block.GetSize().y / 2 + pointer.GetCircleRadius()) {
	//	pointer.body.Repulsion( - block.GetAngle());
	//	pointer.body.TimeReset();
	//}




	if (Input::GetKeyTrigger(VK_S)) {
		SetOldScene(GAMESCENE);			//currentScene“o˜^‘O‚É
		SetCurrentScene(TITLESCENE);	//oldScene‚ÉŽ©g‚ÌƒV[ƒ“ƒ^ƒO‚ð“o˜^‚µ‚È‚¢‚Æ‚¢‚¯‚È‚¢
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