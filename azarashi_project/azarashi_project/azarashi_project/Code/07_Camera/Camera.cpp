#include "Camera.h"

using namespace DirectX;

DirectX::XMVECTOR Camera::m_position = { 0.0f,0.0f,-50.0f };//cameraの位置用の変数
DirectX::XMVECTOR Camera::m_target = { 0.0f,0.0f,0.0f };
DirectX::XMVECTOR Camera::m_upDirection = { 0.0f, 1.0f, 0.0f };
DirectX::XMMATRIX Camera::m_viewMatrix;//向きや回転率などを計算し、描画内容を決めたもの

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
}

void Camera::SetPosition(XMVECTOR v)
{
    m_position = v;
}

void Camera::SetTarget(XMVECTOR v)
{
    m_target = v;
}
