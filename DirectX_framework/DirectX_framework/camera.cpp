#include "Camera.h"
//=======================================
//コンストラクト
//=======================================
Camera::Camera()
{


}

//=======================================
//デストラクト
//=======================================
Camera::~Camera()
{


}

//=======================================
//初期化処理
//=======================================
void Camera::Init()
{
	
}

//=======================================
//更新処理
//=======================================
void Camera::Update()
{
	
}

//=======================================
//描画処理
//=======================================
void Camera::Draw()
{
	
}

//=======================================
//終了処理
//=======================================
void Camera::Uninit()
{

}

//=======================================
//cameraの位置のセッター
//=======================================
void Camera::SetPosition(float x, float y, float z)
{
    m_position.x = x;
    m_position.y = y;
    m_position.z = z;

}

//=======================================
//cameraの回転率のセッター
//=======================================
void Camera::SetRotation(DirectX::XMFLOAT3& rotation)
{



}
//=======================================
//cameraの回転率のセッター
//=======================================
DirectX::XMMATRIX Camera::GetViewMatrix()
{

    return m_viewMatrix;

}

//=======================================
//cameraの回転率のセッター
//=======================================
DirectX::XMMATRIX Camera::GetProjectionMatrix()
{
    return m_projectionMatrix;
}

void Camera::UpdateViewMatrix()
{
    // ビュー行列を計算
    DirectX::XMVECTOR viewPos = DirectX::XMVectorSet(m_position.x, m_position.y, m_position.z, 1.0f);
    DirectX::XMVECTOR viewRot = DirectX::XMVectorAdd(viewPos, DirectX::XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f));
    DirectX::XMVECTOR viewUp = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

    m_viewMatrix = DirectX::XMMatrixLookAtLH(viewPos, viewRot, viewUp);
}

void Camera::UpdateProjectionMatrix()
{
   /* //プロジェクション変換行列
   m_projectionMatrix = DirectX::XMMatrixOrthographicLH(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 3.0f);
   m_projectionMatrix = DirectX::XMMatrixTranspose(m_projectionMatrix);

    // 射影行列を計算
    float fov = DirectX::XM_PIDIV4;
    float aspectRatio = 16.0f / 9.0f;
    float nearZ = 0.1f;
    float farZ = 1000.0f;

    m_projectionMatrix = DirectX::XMMatrixPerspectiveFovLH(fov, aspectRatio, nearZ, farZ);*/

    // 射影行列を計算
    float viewWidth = SCREEN_WIDTH;  // 画面の幅
    float viewHeight = SCREEN_HEIGHT; // 画面の高さ
    float nearZ = 0.1f;
    float farZ = 1000.0f;

    m_projectionMatrix = DirectX::XMMatrixOrthographicLH(viewWidth, viewHeight, nearZ, farZ);

}

DirectX::XMFLOAT3 Camera::GetPosition()
{
    return m_position;
}