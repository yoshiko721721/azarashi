#include "Camera.h"
#include "../03_GameMainFile/Game/GamePointer.h"

using namespace DirectX;

DirectX::XMVECTOR Camera::m_position = { 0.0f,0.0f,-50.0f };//cameraの位置用の変数
DirectX::XMVECTOR Camera::m_target = { 0.0f,0.0f,0.0f };
DirectX::XMVECTOR Camera::m_upDirection = { 0.0f, 1.0f, 0.0f };
DirectX::XMMATRIX Camera::m_viewMatrix;//向きや回転率などを計算し、描画内容を決めたもの

const int WORLD_WIDTH = 50;      // ワールドの横幅
const int WORLD_HEIGHT = 60;     // ワールドの縦幅
extern GamePointer* AZARASHI;			//外部からプレイヤーをカメラに

DirectX::XMMATRIX Camera::GetViewMatrix()
{
    return m_viewMatrix;
}

void Camera::Init()
{
    m_viewMatrix = XMMatrixLookAtLH(m_position, m_target, m_upDirection);
}

void Camera::Update()
{
    m_viewMatrix = XMMatrixLookAtLH(m_position, m_target, m_upDirection);

    //float CameraMoveCounter = 0.0f;	//カメラフォーローカウンター
    //float CmCnt = 0.0f;	//カメラフォーローカウンター
    //bool FollowPlayer = false;	//プレイヤーフォーローフラグ
    //XMVECTOR playerPos = AZARASHI->GetPos ( );
    constexpr float smoothSpeedX = 0.02f; // Xフォーロー速度
    constexpr float smoothSpeedY = 0.03f; // Yフォーロー速度

    // プレイヤーをフォロー
    //m_Position.x = m_Position.x + ( playerPos.x - m_Position.x ) * smoothSpeedX;
    //m_Target.x = m_Position.x;

    // プレイヤーがウィンドウの半分以上にいる時カウント
    ////if ( playerPos.y > m_Scale.y / 2 ) {
    ////	if ( CmCnt == 0.0f )
    ////	{
    ////		CmCnt = 2.0f;
    ////	}
    ////}

    ////if ( CmCnt > 0.0f ) {
    ////	CmCnt -= 1.0f / 60.0f;  // １秒60フレーム
    ////	if ( CmCnt <= 0.0f ) {
    ////		FollowPlayer = true;
    ////	}
    ////}

    ////if ( playerPos.y - m_Position.y==0.0f )
    ////{
    ////	FollowPlayer = false;
    ////}

        // 徐々にフォーロー
    ////if ( FollowPlayer )
    ////{
    //m_Position.y = m_Position.y + ( playerPos.y - m_Position.y ) * smoothSpeedY;
    //m_Target.y = m_Position.y;
   ////}

     // プレイヤーが壁に到着した時の処理
    //if ( m_Position.x < -WORLD_WIDTH / 2 ) {
    //    m_Position.x = -WORLD_WIDTH / 2;
    //    m_Target.x = -WORLD_WIDTH / 2;
    //}
    //if ( m_Position.x > WORLD_WIDTH / 2 ) {
    //    m_Position.x = WORLD_WIDTH / 2;
    //    m_Target.x = WORLD_WIDTH / 2;
    //}
    //if ( m_Position.y < 0 ) {
    //    m_Position.y = 0;
    //    m_Target.y = 0;
    //}
    //if ( m_Position.y > WORLD_HEIGHT / 2 ) {
    //    m_Position.y = WORLD_HEIGHT / 2;
    //    m_Target.y = WORLD_HEIGHT / 2;
    //}
}

void Camera::SetPosition(XMVECTOR v)
{
    m_position = v;
}

void Camera::SetTarget(XMVECTOR v)
{
    m_target = v;
}
