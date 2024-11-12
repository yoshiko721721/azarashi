#include "Camera.h"
//=======================================
//�R���X�g���N�g
//=======================================
Camera::Camera()
{


}

//=======================================
//�f�X�g���N�g
//=======================================
Camera::~Camera()
{


}

//=======================================
//����������
//=======================================
void Camera::Init()
{
	
}

//=======================================
//�X�V����
//=======================================
void Camera::Update()
{
	
}

//=======================================
//�`�揈��
//=======================================
void Camera::Draw()
{
	
}

//=======================================
//�I������
//=======================================
void Camera::Uninit()
{

}

//=======================================
//camera�̈ʒu�̃Z�b�^�[
//=======================================
void Camera::SetPosition(float x, float y, float z)
{
    m_position.x = x;
    m_position.y = y;
    m_position.z = z;

}

//=======================================
//camera�̉�]���̃Z�b�^�[
//=======================================
void Camera::SetRotation(DirectX::XMFLOAT3& rotation)
{



}
//=======================================
//camera�̉�]���̃Z�b�^�[
//=======================================
DirectX::XMMATRIX Camera::GetViewMatrix()
{

    return m_viewMatrix;

}

//=======================================
//camera�̉�]���̃Z�b�^�[
//=======================================
DirectX::XMMATRIX Camera::GetProjectionMatrix()
{
    return m_projectionMatrix;
}

void Camera::UpdateViewMatrix()
{
    // �r���[�s����v�Z
    DirectX::XMVECTOR viewPos = DirectX::XMVectorSet(m_position.x, m_position.y, m_position.z, 1.0f);
    DirectX::XMVECTOR viewRot = DirectX::XMVectorAdd(viewPos, DirectX::XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f));
    DirectX::XMVECTOR viewUp = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

    m_viewMatrix = DirectX::XMMatrixLookAtLH(viewPos, viewRot, viewUp);
}

void Camera::UpdateProjectionMatrix()
{
   /* //�v���W�F�N�V�����ϊ��s��
   m_projectionMatrix = DirectX::XMMatrixOrthographicLH(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 3.0f);
   m_projectionMatrix = DirectX::XMMatrixTranspose(m_projectionMatrix);

    // �ˉe�s����v�Z
    float fov = DirectX::XM_PIDIV4;
    float aspectRatio = 16.0f / 9.0f;
    float nearZ = 0.1f;
    float farZ = 1000.0f;

    m_projectionMatrix = DirectX::XMMatrixPerspectiveFovLH(fov, aspectRatio, nearZ, farZ);*/

    // �ˉe�s����v�Z
    float viewWidth = SCREEN_WIDTH;  // ��ʂ̕�
    float viewHeight = SCREEN_HEIGHT; // ��ʂ̍���
    float nearZ = 0.1f;
    float farZ = 1000.0f;

    m_projectionMatrix = DirectX::XMMatrixOrthographicLH(viewWidth, viewHeight, nearZ, farZ);

}

DirectX::XMFLOAT3 Camera::GetPosition()
{
    return m_position;
}