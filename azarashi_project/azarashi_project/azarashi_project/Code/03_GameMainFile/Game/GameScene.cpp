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

	

	//���ɓ����������@�Փ˔���
	if (block.collider.CheckCollision_Box_Circle(&pointer, &block) )
	{
		
		pointer.body.Repulsion(pointer.GetFrictionResistance());			//����
		pointer.body.VectorPruductAngle(&pointer.body.vector,
										 block.GetAngle(),					//�p�x�ɍ��킹�č��W�ϊ�
										 pointer.GetFrictionResistance());
		pointer.RotateTexture(block.GetFrictionRasistance());				//���ړ��ƘA�������摜�̉�]

	}





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