#include"TitleScene.h"

void TitleScene::Init()
{
	backGround.Init();
}
void TitleScene::Update()
{

	backGround.Update();


	if (Input::GetKeyTrigger(VK_A)) {
		SetOldScene(TITLESCENE);	//�`�F���W�O��oldScene�𑀍�
		SetCurrentScene(GAMESCENE);	//������oldScene�����Ēu���Ȃ��Ƒ��̃V�[���őJ�ڏo���Ȃ�
	}


}
void TitleScene::Draw()
{
	backGround.Draw();
}
void TitleScene::Uninit()
{
	backGround.Uninit();
}



