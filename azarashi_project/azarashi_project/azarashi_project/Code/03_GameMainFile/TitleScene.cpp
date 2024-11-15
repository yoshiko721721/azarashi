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
		SetOldScene(TITLESCENE);	//チェンジ前のoldSceneを操作
		SetCurrentScene(GAMESCENE);	//ここでoldSceneを入れて置かないと他のシーンで遷移出来ない
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


