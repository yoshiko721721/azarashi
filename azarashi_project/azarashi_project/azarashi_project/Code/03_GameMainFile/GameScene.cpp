#include "GameScene.h"

void GameScene::Init()
{

	sample.Init(L"Asset/pic/MatsuFace_transparent.png");	

}
void GameScene::Update()
{
	sample.SetSize(100, 100, 0);
	sample.SetPos(300, 0, 0);

	//E�����������^�C�g���V�[���Ɉړ�
	if (input.GetKeyPress(VK_S)) {
		SetOldScene(GAMESCENE);			//currentScene�o�^�O��
		SetCurrentScene(TITLESCENE);	//oldScene�Ɏ��g�̃V�[���^�O��o�^���Ȃ��Ƃ����Ȃ�
	}

}
void GameScene::Draw()
{
	sample.Draw();
}
void GameScene::Uninit()
{
	sample.Uninit();
}