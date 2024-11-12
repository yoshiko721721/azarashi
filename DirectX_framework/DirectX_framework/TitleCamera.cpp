#include "TitleCamera.h"

//=======================================
//初期化処理
//=======================================
void TitleCamera::Init()
{
    // 初期位置と回転を設定
    m_position = DirectX::XMFLOAT3(2.0f, 0.0f, 0.0f);
    m_rotation = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);

    // ビュー行列と射影行列を更新
    UpdateViewMatrix();
    UpdateProjectionMatrix();

}

//=======================================
//更新処理
//=======================================
void TitleCamera::Update()
{
    input.Update();
    DirectX::XMFLOAT3 pos = GetPosition();
    if (input.GetKeyPress(VK_LEFT))
    {
        pos.x -= 0.5f;
    }
    SetPosition(pos.x, pos.y, pos.z);
    UpdateViewMatrix();
    UpdateProjectionMatrix();
}

//=======================================
//描画処理
//=======================================
void TitleCamera::Draw()
{

}

//=======================================
//終了処理
//=======================================
void TitleCamera::Uninit()
{


}

