#include"TitleScene.h"

void TitleScene::Init()
{
	sample.Init(L"Asset/pic/MatsuFace_transparent.png");
}
void TitleScene::Update()
{




	sample.SetSize(100, 100,   0);
	sample.SetPos (  0,   0,   0);
	if (input.GetKeyPress(VK_A)) {
		SetOldScene(TITLESCENE);	//�`�F���W�O��oldScene�𑀍�
		SetCurrentScene(GAMESCENE);	//������oldScene�����Ēu���Ȃ��Ƒ��̃V�[���őJ�ڏo���Ȃ�
	}


}
void TitleScene::Draw()
{
	sample.Draw();
}
void TitleScene::Uninit()
{
	sample.Uninit();
}


