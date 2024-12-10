#include"TitleScene.h"

void TitleScene::Init()
{
	backGround.Init();
}
void TitleScene::Update()
{

	backGround.Update();


	if (Input::GetKeyTrigger(VK_A)) {
		SetOldScene(TITLESCENE);	//チェンジ前のoldSceneを操作
		SetCurrentScene(GAMESCENE);	//ここでoldSceneを入れて置かないと他のシーンで遷移出来ない
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



