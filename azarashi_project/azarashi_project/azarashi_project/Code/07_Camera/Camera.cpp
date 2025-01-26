#include "Camera.h"
#include <vector> 

using namespace DirectX;

DirectX::XMVECTOR Camera::m_Position = { 0.0f,0.0f,-50.0f };	//camera�̈ʒu�p�̕ϐ�
DirectX::XMVECTOR Camera::m_Target = { 0.0f,0.0f,0.0f };		//target�̈ʒu
DirectX::XMVECTOR Camera::m_upDirection = { 0.0f, 1.0f, 0.0f }; //�����
DirectX::XMMATRIX Camera::m_viewMatrix;							//�������]���Ȃǂ��v�Z���A�`����e�����߂�����

const int WORLD_WIDTH = 50;      // ���[���h�̉����A�e�X�g�p�l
const int WORLD_HEIGHT = 60;     // ���[���h�̏c���A�e�X�g�p�l

Object* Camera::lockObj;

DirectX::XMMATRIX Camera::GetViewMatrix ( )
{
	return m_viewMatrix;
}

Camera::Camera()
{
}

void Camera::Init ( )
{
	m_viewMatrix = XMMatrixLookAtLH ( m_Position , m_Target , m_upDirection );

}

void Camera::Update ( )
{
	m_viewMatrix = XMMatrixLookAtLH ( m_Position , m_Target , m_upDirection );

	if (lockObj) {
		XMFLOAT3 pos = lockObj->GetPos();
		XMVECTOR posV = { pos.x , pos.y ,0 ,0 };

		static float range = 200;

		float length = pow(pos.x, 2) + pow(pos.y, 2);

		if (pow(range, 2) < length) {
			static float rate = 0.9f;
			XMVECTOR resultV = XMVectorLerp(posV, XMVECTOR{ XMVectorGetX(m_Position), XMVectorGetY(m_Position), 0, 0 }, rate);
			m_Position = { XMVectorGetX(resultV), XMVectorGetY(resultV), -1, 0 };
			m_Target = { XMVectorGetX(resultV), XMVectorGetY(resultV), 0.5, 0 };

			m_viewMatrix = XMMatrixLookAtLH(m_Position, m_Target, m_upDirection);
		}

	}

}

void Camera::SetPosition ( XMVECTOR v )
{
	m_Position = v;
}

void Camera::SetTarget ( XMVECTOR v )
{
	m_Target = v;
}

void Camera::Lock(Object* obj)
{
	lockObj = obj;
}

void Camera::UnLock()
{
	lockObj = nullptr;
}
