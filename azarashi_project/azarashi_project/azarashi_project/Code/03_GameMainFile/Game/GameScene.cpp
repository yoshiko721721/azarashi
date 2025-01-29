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
	//���ɓ����������@�Փ˔���
	collision = BoxCollider::ColliderWithCircle(&pointer, &block);

	pointer.Update();
	block.Update();

	//���ړ��ƘA�������摜�̉�]
	if (pointer.azaNum == CIRCLE) {
		pointer.RotateTexture();
	}

	if (Input::GetKeyTrigger(VK_S)) {
		Application::GetInstance()->ChangeScene(TITLESCENE);	//������oldScene�����Ēu���Ȃ��Ƒ��̃V�[���őJ�ڏo���Ȃ�
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