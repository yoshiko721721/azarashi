#include <windows.h>
#include "SceneManager.h"
#include "Game.h"
//#include "TitleScene.h" // 初期シーンのヘッダーをインクルード

void Game::Init(HWND hWnd)
{
    // DirectXの初期化
    D3D_Create(hWnd);
    // 初期シーンの設定
    sceneManager.ChangeScene(std::make_unique<TitleScene>());
}

void Game::Update()
{
    // ゲーム全体の更新処理
      input.Update();
 
    if (input.GetKeyPress(VK_Q))
    {
        sceneManager.ChangeScene(std::make_unique<GameScene>());
    }
    if (input.GetKeyPress(VK_E))
    {
        sceneManager.ChangeScene(std::make_unique<TitleScene>());
    }

    sceneManager.Update();//SceneManagerのUpdateに移動してシーン自体を更新する
}

void Game::Draw()
{
    // ゲーム全体の描画処理
    sceneManager.Draw();
}

void Game::Uninit()
{
    // ゲーム全体の終了処理
    D3D_Release();
}

bool Game::ShouldExit()
{
    // 終了条件の判定
    return 0;
}