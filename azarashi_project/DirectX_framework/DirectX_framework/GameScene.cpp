#include "GameScene.h"
//------------------------------
//Gameシーン自体のInit～Uninit
//------------------------------
void GameScene::Init()
{
    // 初期化処理
    GameBackGround.Init();
    GamePointer.Init();
    GameBlock.Init();
}

void GameScene::Update()
{
    // 更新処理
    GameBackGround.Update();
    GamePointer.Update();
    GameBlock.Update();
    GameCamera.Update();
}

void GameScene::Draw()
{   // 描画処理
    D3D_StartRender();  //描画開始
    GameBackGround.Draw(&GameCamera);
    GamePointer.Draw(&GameCamera);
    GameBlock.Draw(&GameCamera);
    D3D_FinishRender(); //描画終了
}

void GameScene::Uninit()
{
    // 終了処理
    GameBackGround.Uninit();
    GamePointer.Uninit();
    GameBlock.Uninit();
    //D3D_Release();//DirectXを終了
}
