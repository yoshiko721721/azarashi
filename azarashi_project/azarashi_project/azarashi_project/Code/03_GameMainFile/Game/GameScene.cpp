#include "GameScene.h"

void GameScene::Init()
{

	sample.Initialize(L"Asset/pic/point.png");	
	sample.SetSize(100, 100, 0);
	sample.SetPos(300, 0, 0);

	backGround.Init();
	pointer.Init();
	block.Init();

}
void GameScene::Update()
{

	//E�����������^�C�g���V�[���Ɉړ�
	
	//backGround.Update();
	pointer.Update();
	block.Update();
	
	if (Input::GetKeyTrigger(VK_RETURN)) {
		pointer.body.AddForce(10.0f,0.0f);
	}

	//���ɓ���������
	if (pointer.GetPos().x >= block.GetPos().x - block.GetSize().x / 2 &&
		pointer.GetPos().x <= block.GetPos().x + block.GetSize().x / 2 &&
		pointer.GetPos().y <= block.GetPos().y + block.GetSize().y / 2 + pointer.GetCircleRadius())
	{

		pointer.body.Repulsion(pointer.GetFrictionResistance());
		pointer.body.HorizonUpdate(&pointer.body.vector, 
									pointer.GetFrictionResistance(),
									block.GetAngle());

		//�n�ʂ̏�Ɉʒu���C��
		pointer.SetPos(pointer.GetPos().x, block.GetPos().y + pointer.GetCircleRadius() + 23, 0);
		pointer.body.VectorPruductAngle(&pointer.body.vector, 
										 block.GetAngle(),
										 pointer.GetFrictionResistance());


		pointer.RotateTexture(block.GetFrictionRasistance());

	}
	else {

	}


	//if (pointer.GetPos().x >= block.GetPos().x   - block.GetSize().x / 2 &&
	//	pointer.GetPos().x <= block.GetPos().x   + block.GetSize().x / 2 &&
	//	pointer.GetPos().y <= pointer.GetPos().y + block.GetSize().y + block.GetSize().y / 2 + pointer.GetCircleRadius()) {
	//	pointer.body.Repulsion( - block.GetAngle());
	//	pointer.body.TimeReset();
	//}

	


	if (Input::GetKeyTrigger(VK_S)) {
		SetOldScene(GAMESCENE);			//currentScene�o�^�O��
		SetCurrentScene(TITLESCENE);	//oldScene�Ɏ��g�̃V�[���^�O��o�^���Ȃ��Ƃ����Ȃ�
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

