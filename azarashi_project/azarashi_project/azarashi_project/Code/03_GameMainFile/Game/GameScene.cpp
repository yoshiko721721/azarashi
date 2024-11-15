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

	//E�����������^�C�g���V�[���Ɉړ�
	backGround.Update();
	pointer.Update();
	block.Update();
	
	if (input.GetKeyPress(VK_S)) {
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