#include "Renderer.h"
#include "Camera.h"
#include "Application.h"
#include "Player.h"

using namespace DirectX::SimpleMath;

const int WORLD_WIDTH = 50;		//���[���h�i�}�b�v�j�̉���
const int WORLD_HEIGHT = 60;		//���[���h�i�}�b�v�j�̏c��
extern Player* aza;			//�O������v���C���[���J������

//=======================================
//����������
//=======================================
void Camera::Init ( )
{
	m_Position = Vector3 ( 0.0f , 0.0f , -50.0f );
	m_Target = Vector3 ( 0.0f , 0.0f , 0.0f );
}


//=======================================
//�X�V����
//=======================================
void Camera::Update ( )
{

	Vector3 player = aza->GetPosition ( );
	//�v���C���[���t�H���[
	m_Position.x = aza->GetPosition ( ).x;
	m_Position.y = aza->GetPosition ( ).y;
	m_Target = aza->GetPosition ( );

	//�v���C���[���ǂɓ�������������
	if ( m_Position.x < -WORLD_WIDTH / 2 ) {	//��ԍ�
		m_Position.x = -WORLD_WIDTH / 2;
		m_Target.x = -WORLD_WIDTH / 2;
	}
	if ( m_Position.x > WORLD_WIDTH / 2 ) {	//��ԉE
		m_Position.x = WORLD_WIDTH / 2;
		m_Target.x = WORLD_WIDTH / 2;
	}
	if ( m_Position.y < 0 ) {	//�n��
		m_Position.y = 0;
		m_Target.y = 0;
	}
	if ( m_Position.y > WORLD_HEIGHT / 2 ) {	//��ԏ�
		m_Position.y = WORLD_HEIGHT / 2;
		m_Target.y = WORLD_HEIGHT / 2;
	}
}

//=======================================
//�`�揈��
//=======================================
void Camera::Draw ( )
{
	// �r���[�ϊ����쐬
	Vector3 up = Vector3 ( 0.0f , 1.0f , 0.0f );
	m_ViewMatrix = DirectX::XMMatrixLookAtLH ( m_Position , m_Target , up ); // ����n�ɂ����@20230511 by suzuki.tomoki
	// DIRECTXTK�̃��\�b�h�͉E��n�@20230511 by suzuki.tomoki
	// �E��n�ɂ���ƂR�p�`���_�������v���ɂȂ�̂ŕ`�悳��Ȃ��Ȃ�̂Œ���
	// ���̃R�[�h�͊m�F�e�X�g�̂��߂Ɏc��
	// m_ViewMatrix = m_ViewMatrix.CreateLookAt(m_Position, m_Target, up);					

	Renderer::SetViewMatrix ( &m_ViewMatrix );

	//�v���W�F�N�V�����s��̐���
	constexpr float fieldOfView = DirectX::XMConvertToRadians ( 45.0f );    // ����p

	float aspectRatio = static_cast< float >( Application::GetWidth ( ) ) / static_cast< float >( Application::GetHeight ( ) );	// �A�X�y�N�g��	
	float nearPlane = 1.0f;       // �j�A�N���b�v
	float farPlane = 1000.0f;      // �t�@�[�N���b�v

	//�v���W�F�N�V�����s��̐���
	Matrix projectionMatrix;
	projectionMatrix = DirectX::XMMatrixPerspectiveFovLH ( fieldOfView , aspectRatio , nearPlane , farPlane );	// ����n�ɂ����@20230511 by suzuki.tomoki
	// DIRECTXTK�̃��\�b�h�͉E��n�@20230511 by suzuki.tomoki
	// �E��n�ɂ���ƂR�p�`���_�������v���ɂȂ�̂ŕ`�悳��Ȃ��Ȃ�̂Œ���
	// ���̃R�[�h�͊m�F�e�X�g�̂��߂Ɏc��
	// projectionMatrix = DirectX::SimpleMath::Matrix::CreatePerspectiveFieldOfView(fieldOfView, aspectRatio, nearPlane, farPlane);

	Renderer::SetProjectionMatrix ( &projectionMatrix );
}


//=======================================
//�I������
//=======================================
void Camera::Uninit ( )
{

}

