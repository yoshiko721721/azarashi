#include "Camera.h"
#include "../03_GameMainFile/Game/GamePointer.h"

using namespace DirectX;

DirectX::XMVECTOR Camera::m_position = { 0.0f,0.0f,-50.0f };//camera�̈ʒu�p�̕ϐ�
DirectX::XMVECTOR Camera::m_target = { 0.0f,0.0f,0.0f };
DirectX::XMVECTOR Camera::m_upDirection = { 0.0f, 1.0f, 0.0f };
DirectX::XMMATRIX Camera::m_viewMatrix;//�������]���Ȃǂ��v�Z���A�`����e�����߂�����

const int WORLD_WIDTH = 50;      // ���[���h�̉���
const int WORLD_HEIGHT = 60;     // ���[���h�̏c��
extern GamePointer* AZARASHI;			//�O������v���C���[���J������

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

    //float CameraMoveCounter = 0.0f;	//�J�����t�H�[���[�J�E���^�[
    //float CmCnt = 0.0f;	//�J�����t�H�[���[�J�E���^�[
    //bool FollowPlayer = false;	//�v���C���[�t�H�[���[�t���O
    //XMVECTOR playerPos = AZARASHI->GetPos ( );
    constexpr float smoothSpeedX = 0.02f; // X�t�H�[���[���x
    constexpr float smoothSpeedY = 0.03f; // Y�t�H�[���[���x

    // �v���C���[���t�H���[
    //m_Position.x = m_Position.x + ( playerPos.x - m_Position.x ) * smoothSpeedX;
    //m_Target.x = m_Position.x;

    // �v���C���[���E�B���h�E�̔����ȏ�ɂ��鎞�J�E���g
    ////if ( playerPos.y > m_Scale.y / 2 ) {
    ////	if ( CmCnt == 0.0f )
    ////	{
    ////		CmCnt = 2.0f;
    ////	}
    ////}

    ////if ( CmCnt > 0.0f ) {
    ////	CmCnt -= 1.0f / 60.0f;  // �P�b60�t���[��
    ////	if ( CmCnt <= 0.0f ) {
    ////		FollowPlayer = true;
    ////	}
    ////}

    ////if ( playerPos.y - m_Position.y==0.0f )
    ////{
    ////	FollowPlayer = false;
    ////}

        // ���X�Ƀt�H�[���[
    ////if ( FollowPlayer )
    ////{
    //m_Position.y = m_Position.y + ( playerPos.y - m_Position.y ) * smoothSpeedY;
    //m_Target.y = m_Position.y;
   ////}

     // �v���C���[���ǂɓ����������̏���
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
