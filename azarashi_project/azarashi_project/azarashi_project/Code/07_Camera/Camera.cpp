#include "Camera.h"
#include <vector>
//#include "../03_GameMainFile/Test/TestStageScene_Nakae.h"
#include "../03_GameMainFile/Game/GamePointer.h"

using namespace DirectX;

DirectX::XMVECTOR Camera::m_Position = { 0.0f,0.0f,-50.0f };//cameraの位置用の変数
DirectX::XMVECTOR Camera::m_Target = { 0.0f,0.0f,0.0f };      //targetの位置
DirectX::XMVECTOR Camera::m_upDirection = { 0.0f, 1.0f, 0.0f }; //上方向
DirectX::XMMATRIX Camera::m_viewMatrix;//向きや回転率などを計算し、描画内容を決めたもの
Object* Camera::lockObj;

const int WORLD_WIDTH = 50;      // ワールドの横幅、テスト用値
const int WORLD_HEIGHT = 60;     // ワールドの縦幅、テスト用値

//const int BLOCKSIZE = 128;

//float x = SCREEN_WIDTH * -1 / 2 + BLOCKSIZE / 2;//どこからスタートするかどうか(変更可能性高め)
//float y = SCREEN_HEIGHT / 2 - BLOCKSIZE / 2;//どこからスタートするかどうか(変更可能性高め)

//GamePointer* p_Player; /*= Application::GetInstance ( )->AddObject<GamePointer> ( x , y , BLOCKSIZE , BLOCKSIZE );*/
//extern GamePointer* AZARASHI; /*= Application::GetInstance ( )->AddObject<GamePointer> ( x , y , BLOCKSIZE , BLOCKSIZE );*/
//外部からプレイヤーをカメラに

DirectX::XMMATRIX Camera::GetViewMatrix ( )
{
	return m_viewMatrix;
}

Camera::Camera ()
{
}

void Camera::Init ( )
{
	m_viewMatrix = XMMatrixLookAtLH ( m_Position , m_Target , m_upDirection );

}

void Camera::Update ( )
{


	////float CameraMoveCounter = 0.0f;	//カメラフォーローカウンター
	////float CmCnt = 0.0f;	//カメラフォーローカウンター
	////bool FollowPlayer = false;	//プレイヤーフォーローフラグ

	//std::vector<GamePointer*>players = Application::GetInstance ( )->GetObjects<GamePointer> ( );
	//if ( players.size ( ) > 0 ) {
	//	XMFLOAT3 playerPos = players[ 0 ]->GetPos ( );       //プレイヤーの座標をゲット
	//	//Camera::m_Position = { playerPos.x , playerPos.y  ,  -50.0f };

	//	float caPx = XMVectorGetX ( m_Position );   //カメラの座標Ｘをゲット
	//	float caPy = XMVectorGetY ( m_Position );    //カメラの座標Yをゲット
	////	float caPz = XMVectorGetZ ( m_Position );    //カメラの座標Zをゲット
	//	float caTx = XMVectorGetX ( m_Target );     //ターゲットの座標Ｘをゲット
	//	float caTy = XMVectorGetY ( m_Target );     //ターゲットの座標Yをゲット
	////	float caTz = XMVectorGetZ ( m_Target );     //ターゲットの座標Zをゲット
	//	constexpr float smoothSpeedX = 0.0002f; // Xフォーロー速度
	//	constexpr float smoothSpeedY = 0.0003f; // Yフォーロー速度

	//	// プレイヤーをフォロー
	//	caPx = caPx + ( playerPos.x - caPx ) * smoothSpeedX;
	//	caTx = caPx;
	//	caPy = caPy + ( playerPos.y - caPy ) * smoothSpeedY;
	//	//if ( caPy < 0.0f ) caPy = 0.0f;
	//	caTy = caPy;


	//	m_Position = XMVectorSet ( caPx , caPy , -50.0f , 0.0f );    //カメラの座標Ｘを更新
	//	m_Target = XMVectorSet ( caTx , caTy , 0.0f , 0.0f );        //ターゲットの座標Ｘを更新


		//m_Position = XMVectorSetY ( m_Position , caPy );    //カメラの座標Yを更新
		//m_Target = XMVectorSetY ( m_Target , caTy );        //ターゲットの座標Yを更新


		// //プレイヤーがウィンドウの半分以上にいる時カウント
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

		//// 徐々にフォーロー
		////if ( FollowPlayer )
		////{
		//caPy = caPy + ( playerPos.y - caPy ) * smoothSpeedY;
		//caTy = caPy;
		//m_Position = XMVectorSetY ( m_Position , caPy );    //カメラの座標Yを更新
		//m_Target = XMVectorSetY ( m_Target , caTy );        //ターゲットの座標Yを更新

	 //  //}

		// // プレイヤーが壁に到着した時の処理
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
		//}

	/*static float a = 0;
	a += 0.1f;
	m_Position = { 0 , a, -50 };*/

	if ( lockObj ) {
		XMFLOAT3  pos = lockObj->GetPos ( );
		XMVECTOR posV = { pos.x, pos.y, 0, 0 };

		static float range = 200;

		float length = pow(pos.x , 2 ) + pow(pos.y, 2);
		
		if ( pow(range, 2) < length )
		{
			static float rate = 0.9f;
			XMVECTOR resultV = XMVectorLerp ( posV , XMVECTOR { XMVectorGetX ( m_Position ), XMVectorGetY ( m_Position ), 0, 0 }, rate );
			m_Position = { XMVectorGetX ( resultV ), XMVectorGetY ( resultV ), -1, 0 };
			m_Target = { XMVectorGetX ( resultV ), XMVectorGetY ( resultV ), 0.5, 0 };

			m_viewMatrix = XMMatrixLookAtLH ( m_Position , m_Target , m_upDirection );
		}
	
	}
	//float CameraMoveCounter = 0.0f;	//カメラフォーローカウンター
	//float CmCnt = 0.0f;	//カメラフォーローカウンター
	//bool FollowPlayer = false;	//プレイヤーフォーローフラグ
	//XMFLOAT3 playerPos = AZARASHI->GetPos ( );       //プレイヤーの座標をゲット
	float caPx = XMVectorGetX ( m_Position );    //カメラの座標Ｘをゲット
	float caPy = XMVectorGetY ( m_Position );    //カメラの座標Yをゲット
	float caPz = XMVectorGetZ ( m_Position );    //カメラの座標Zをゲット
	float caTx = XMVectorGetX ( m_Target );     //ターゲットの座標Ｘをゲット
	float caTy = XMVectorGetY ( m_Target );     //ターゲットの座標Yをゲット
	float caTz = XMVectorGetZ ( m_Target );     //ターゲットの座標Zをゲット
	constexpr float smoothSpeedX = 0.02f; // Xフォーロー速度
	constexpr float smoothSpeedY = 0.03f; // Yフォーロー速度

	// プレイヤーをフォロー
	//caPx = caPx + ( playerPos.x - caPx ) * smoothSpeedX;
	//caTx = caPx;

	//m_Position = XMVectorSetX ( m_Position , caPx );    //カメラの座標Ｘを更新
	//m_Target = XMVectorSetX ( m_Target , caTx );        //ターゲットの座標Ｘを更新

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

void Camera::Lock ( Object* obj )
{
	lockObj = obj;
}

void Camera::Unlock ( )
{
	lockObj = nullptr;
}
