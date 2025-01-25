#include "Camera.h"
//#include "../03_GameMainFile/Test/TestStageScene_Nakae.h"

using namespace DirectX;

DirectX::XMVECTOR Camera::m_Position = { 0.0f,0.0f,-50.0f };//cameraの位置用の変数
DirectX::XMVECTOR Camera::m_Target = { 0.0f,0.0f,0.0f };      //targetの位置
DirectX::XMVECTOR Camera::m_upDirection = { 0.0f, 1.0f, 0.0f }; //上方向
DirectX::XMMATRIX Camera::m_viewMatrix;//向きや回転率などを計算し、描画内容を決めたもの

const int WORLD_WIDTH = 50;      // ワールドの横幅、テスト用値
const int WORLD_HEIGHT = 60;     // ワールドの縦幅、テスト用値

//const int BLOCKSIZE = 128;

//float x = SCREEN_WIDTH * -1 / 2 + BLOCKSIZE / 2;//どこからスタートするかどうか(変更可能性高め)
//float y = SCREEN_HEIGHT / 2 - BLOCKSIZE / 2;//どこからスタートするかどうか(変更可能性高め)

GamePointer* p_Player; /*= Application::GetInstance ( )->AddObject<GamePointer> ( x , y , BLOCKSIZE , BLOCKSIZE );*/
//外部からプレイヤーをカメラに

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

	//float CameraMoveCounter = 0.0f;	//カメラフォーローカウンター
	//float CmCnt = 0.0f;	//カメラフォーローカウンター
	//bool FollowPlayer = false;	//プレイヤーフォーローフラグ
	Scene* pTestP = Application::GetInstance ( )->GetCurrentScene ( );

	TestScene_You* aaa = dynamic_cast< TestScene_You* >( pTestP );
	if ( aaa != NULL )
	{
	p_Player = aaa->GetPlayer ( );

	XMFLOAT3 playerPos = p_Player->GetPos ( );       //プレイヤーの座標をゲット

	float caPx = XMVectorGetX ( m_Position );    //カメラの座標Ｘをゲット
	float caPy = XMVectorGetY ( m_Position );    //カメラの座標Yをゲット
	float caPz = XMVectorGetZ ( m_Position );    //カメラの座標Zをゲット
	float caTx = XMVectorGetX ( m_Target );     //ターゲットの座標Ｘをゲット
	float caTy = XMVectorGetY ( m_Target );     //ターゲットの座標Yをゲット
	float caTz = XMVectorGetZ ( m_Target );     //ターゲットの座標Zをゲット
	constexpr float smoothSpeedX = 0.02f; // Xフォーロー速度
	constexpr float smoothSpeedY = 0.03f; // Yフォーロー速度

	// プレイヤーをフォロー
	caPx = caPx + ( playerPos.x - caPx ) * smoothSpeedX;
	caTx = caPx;

	m_Position = XMVectorSetX ( m_Position , caPx );    //カメラの座標Ｘを更新
	m_Target = XMVectorSetX ( m_Target , caTx );        //ターゲットの座標Ｘを更新

	}

	// プレイヤーがウィンドウの半分以上にいる時カウント
	////if ( playerPos.y > SCREEN_HEIGHT / 2 ) {
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

	////if ( playerPos.y - caPy==0.0f )
	////{
	////	FollowPlayer = false;
	////}

		// 徐々にフォーロー
	////if ( FollowPlayer )
	////{
	//caPy = caPy + ( playerPos.y - caPy ) * smoothSpeedY;
	//caTy = caPy;
	//m_Position = XMVectorSetY ( m_Position , caPy );    //カメラの座標Yを更新
	//m_Target = XMVectorSetY ( m_Target , caTy );        //ターゲットの座標Yを更新

   ////}

	  //プレイヤーが壁に到着した時の処理
	//if ( caPx < -WORLD_WIDTH / 2 ) {        
	//    caPx = -WORLD_WIDTH / 2;
	//    caTx = -WORLD_WIDTH / 2;

	//    m_Position = XMVectorSetX ( m_Position , caPx );    //カメラの座標Ｘを更新
	//    m_Target = XMVectorSetX ( m_Target , caTx );        //ターゲットの座標Ｘを更新
	//}
	//if ( caPx > WORLD_WIDTH / 2 ) {        
	//    caPx = WORLD_WIDTH / 2;
	//    caTx = WORLD_WIDTH / 2;

	//    m_Position = XMVectorSetX ( m_Position , caPx );    //カメラの座標Ｘを更新
	//    m_Target = XMVectorSetX ( m_Target , caTx );        //ターゲットの座標Ｘを更新
	//}
	//if ( caPy < 0 ) {       
	//    caPy = 0;
	//    caTy = 0;

	//    m_Position = XMVectorSetY ( m_Position , caPy );    //カメラの座標Yを更新
	//    m_Target = XMVectorSetY ( m_Target , caTy );        //ターゲットの座標Yを更新
	//}
	//if ( caPy > WORLD_HEIGHT / 2 ) {        
	//    caPy = WORLD_HEIGHT / 2;
	//    caTy = WORLD_HEIGHT / 2;

	//    m_Position = XMVectorSetY ( m_Position , caPy );    //カメラの座標Yを更新
	//    m_Target = XMVectorSetY ( m_Target , caTy );        //ターゲットの座標Yを更新
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
