#include "TitleScene.h"
//------------------------------
//Titleシーン自体のInit～Uninit
//------------------------------
void TitleScene::Init()
{
    // 初期化処理
    TitleBackground.Init();
    TitleCamera.Init();
}

void TitleScene::Update()
{
    // 更新処理
    TitleBackground.Update();
    TitleCamera.Update();
}

void TitleScene::Draw()
{
    // 描画処理
    D3D_StartRender();  //描画開始
    TitleBackground.Draw(&TitleCamera);
    D3D_FinishRender(); //描画終了
}

void TitleScene::Uninit()
{
    //終了処理
    TitleBackground.Uninit();
    //input.Uninit();
    //D3D_Release();//DirectXを終了
}
