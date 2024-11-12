#include "GameCamera.h"
//=======================================
//初期化処理
//=======================================
void GameCamera::Init()//2024/10/28
{
    // 初期位置と回転を設定
    m_position = DirectX::XMFLOAT3(0.0f, 0.0f, -5.0f);
    m_rotation = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);

    // ビュー行列と射影行列を更新
    UpdateViewMatrix();
    UpdateProjectionMatrix();
}

//=======================================
//更新処理
//=======================================
void GameCamera::Update()
{
    input.Update();
    DirectX::XMFLOAT3 pos = GetPosition();
    if (input.GetKeyPress(VK_RIGHT))
    {
        pos.x += 0.5f;
    }
    SetPosition(pos.x, pos.y, pos.z);
    //UpdateViewMatrix();
}

//=======================================
//描画処理
//=======================================
void GameCamera::Draw()
{


}

//=======================================
//終了処理
//=======================================
void GameCamera::Uninit()
{


}


