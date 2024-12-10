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
void GameCamera::Update(float targetPosX,float targetPosY)
{

    target = { targetPosX ,targetPosY };        //基準のターゲット座標を代入
    DirectX::XMFLOAT3 pos = GetPosition();

    //// 単位ベクトル取得
    //DirectX::XMFLOAT3 player_to_target = DirectX::XMFLOAT3(target.x - player_pos.x, target_pos.y - player_pos.y, target_pos.z - player_pos.z);
    //float length = sqrtf(powf(player_to_target.x, 2.0f) + powf(player_to_target.y, 2.0f) + powf(player_to_target.z, 2.0f));
    //DirectX::XMFLOAT3 unitvec_player_to_target = DirectX::XMFLOAT3(player_to_target.x / length, player_to_target.y / length, player_to_target.z / length);



    if (Input::GetKeyPress(VK_RIGHT))
    {
        pos.x += 5.0f;
    }
    SetPosition(pos.x, pos.y);
    GetViewMatrix();
    GetViewMatrix();
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

//コンストラクタ＜－使用しない
GameCamera::GameCamera()
{
}

//コンストラクタ
GameCamera::GameCamera(float screenWidth, float screenHeight)
{
    
}


//座標セッター
void GameCamera::SetPosition(float x, float y)
{
    
}

//ビュー行列ゲッター
DirectX::XMMATRIX GameCamera::GetViewMatrix() const
{
    return viewMatrix;
}

//射影行列ゲッター
DirectX::XMMATRIX GameCamera::GetProjectionMatrix() const
{
    return projectionMatrix;
}

//射影行列更新
void GameCamera::updateViewMatrix()
{
    viewMatrix = DirectX::XMMatrixTranslation(-position.x, -position.y, 0.0f); 
}





