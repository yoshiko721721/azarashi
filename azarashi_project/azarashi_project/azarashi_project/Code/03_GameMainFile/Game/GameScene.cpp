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

	//���ɓ����������@�Փ˔���
	if (BoxCollider::ColliderWithCircle(&pointer, &block) )
	{
		if (Input::GetKeyTrigger(VK_RETURN)) {
			pointer.body.AddForce(0.0f, -30.0f);
		}

		//�������̍X�V
		pointer.body.HorizonUpdate(&pointer.body.vector,					
									pointer.GetFrictionResistance(),
									block.GetAngle());
		//����
		pointer.body.Repulsion(pointer.GetFrictionResistance(), block.GetAngle());
		
		pointer.body.DampingVector(pointer.damping , pointer.azaNum);


	}
	
	//���ړ��ƘA�������摜�̉�]
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