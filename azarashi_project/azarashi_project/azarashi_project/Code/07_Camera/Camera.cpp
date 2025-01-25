#include "Camera.h"
//#include "../03_GameMainFile/Test/TestStageScene_Nakae.h"

using namespace DirectX;

DirectX::XMVECTOR Camera::m_Position = { 0.0f,0.0f,-50.0f };//camera�̈ʒu�p�̕ϐ�
DirectX::XMVECTOR Camera::m_Target = { 0.0f,0.0f,0.0f };      //target�̈ʒu
DirectX::XMVECTOR Camera::m_upDirection = { 0.0f, 1.0f, 0.0f }; //�����
DirectX::XMMATRIX Camera::m_viewMatrix;//�������]���Ȃǂ��v�Z���A�`����e�����߂�����

const int WORLD_WIDTH = 50;      // ���[���h�̉����A�e�X�g�p�l
const int WORLD_HEIGHT = 60;     // ���[���h�̏c���A�e�X�g�p�l

//const int BLOCKSIZE = 128;

//float x = SCREEN_WIDTH * -1 / 2 + BLOCKSIZE / 2;//�ǂ�����X�^�[�g���邩�ǂ���(�ύX�\������)
//float y = SCREEN_HEIGHT / 2 - BLOCKSIZE / 2;//�ǂ�����X�^�[�g���邩�ǂ���(�ύX�\������)

GamePointer* p_Player; /*= Application::GetInstance ( )->AddObject<GamePointer> ( x , y , BLOCKSIZE , BLOCKSIZE );*/
//�O������v���C���[���J������

DirectX::XMMATRIX Camera::GetViewMatrix ( )
{
	return m_viewMatrix;
}

void Camera::Init ( )
{
	m_viewMatrix = XMMatrixLookAtLH ( m_Position , m_Target , m_upDirection );

}

void Camera::Update ( )
{
	m_viewMatrix = XMMatrixLookAtLH ( m_Position , m_Target , m_upDirection );

	//float CameraMoveCounter = 0.0f;	//�J�����t�H�[���[�J�E���^�[
	//float CmCnt = 0.0f;	//�J�����t�H�[���[�J�E���^�[
	//bool FollowPlayer = false;	//�v���C���[�t�H�[���[�t���O
	Scene* pTestP = Application::GetInstance ( )->GetCurrentScene ( );

	TestScene_You* aaa = dynamic_cast< TestScene_You* >( pTestP );
	if ( aaa != NULL )
	{
	p_Player = aaa->GetPlayer ( );

	XMFLOAT3 playerPos = p_Player->GetPos ( );       //�v���C���[�̍��W���Q�b�g

	float caPx = XMVectorGetX ( m_Position );    //�J�����̍��W�w���Q�b�g
	float caPy = XMVectorGetY ( m_Position );    //�J�����̍��WY���Q�b�g
	float caPz = XMVectorGetZ ( m_Position );    //�J�����̍��WZ���Q�b�g
	float caTx = XMVectorGetX ( m_Target );     //�^�[�Q�b�g�̍��W�w���Q�b�g
	float caTy = XMVectorGetY ( m_Target );     //�^�[�Q�b�g�̍��WY���Q�b�g
	float caTz = XMVectorGetZ ( m_Target );     //�^�[�Q�b�g�̍��WZ���Q�b�g
	constexpr float smoothSpeedX = 0.02f; // X�t�H�[���[���x
	constexpr float smoothSpeedY = 0.03f; // Y�t�H�[���[���x

	// �v���C���[���t�H���[
	caPx = caPx + ( playerPos.x - caPx ) * smoothSpeedX;
	caTx = caPx;

	m_Position = XMVectorSetX ( m_Position , caPx );    //�J�����̍��W�w���X�V
	m_Target = XMVectorSetX ( m_Target , caTx );        //�^�[�Q�b�g�̍��W�w���X�V

	}

	// �v���C���[���E�B���h�E�̔����ȏ�ɂ��鎞�J�E���g
	////if ( playerPos.y > SCREEN_HEIGHT / 2 ) {
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

	////if ( playerPos.y - caPy==0.0f )
	////{
	////	FollowPlayer = false;
	////}

		// ���X�Ƀt�H�[���[
	////if ( FollowPlayer )
	////{
	//caPy = caPy + ( playerPos.y - caPy ) * smoothSpeedY;
	//caTy = caPy;
	//m_Position = XMVectorSetY ( m_Position , caPy );    //�J�����̍��WY���X�V
	//m_Target = XMVectorSetY ( m_Target , caTy );        //�^�[�Q�b�g�̍��WY���X�V

   ////}

	  //�v���C���[���ǂɓ����������̏���
	//if ( caPx < -WORLD_WIDTH / 2 ) {        
	//    caPx = -WORLD_WIDTH / 2;
	//    caTx = -WORLD_WIDTH / 2;

	//    m_Position = XMVectorSetX ( m_Position , caPx );    //�J�����̍��W�w���X�V
	//    m_Target = XMVectorSetX ( m_Target , caTx );        //�^�[�Q�b�g�̍��W�w���X�V
	//}
	//if ( caPx > WORLD_WIDTH / 2 ) {        
	//    caPx = WORLD_WIDTH / 2;
	//    caTx = WORLD_WIDTH / 2;

	//    m_Position = XMVectorSetX ( m_Position , caPx );    //�J�����̍��W�w���X�V
	//    m_Target = XMVectorSetX ( m_Target , caTx );        //�^�[�Q�b�g�̍��W�w���X�V
	//}
	//if ( caPy < 0 ) {       
	//    caPy = 0;
	//    caTy = 0;

	//    m_Position = XMVectorSetY ( m_Position , caPy );    //�J�����̍��WY���X�V
	//    m_Target = XMVectorSetY ( m_Target , caTy );        //�^�[�Q�b�g�̍��WY���X�V
	//}
	//if ( caPy > WORLD_HEIGHT / 2 ) {        
	//    caPy = WORLD_HEIGHT / 2;
	//    caTy = WORLD_HEIGHT / 2;

	//    m_Position = XMVectorSetY ( m_Position , caPy );    //�J�����̍��WY���X�V
	//    m_Target = XMVectorSetY ( m_Target , caTy );        //�^�[�Q�b�g�̍��WY���X�V
	//}

}

void Camera::SetPosition ( XMVECTOR v )
{
	m_Position = v;
}

void Camera::SetTarget ( XMVECTOR v )
{
	m_Target = v;
}
