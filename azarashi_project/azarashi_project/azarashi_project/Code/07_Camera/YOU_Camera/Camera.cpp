#include "Renderer.h"
#include "Camera.h"
#include "Application.h"
#include "Player.h"

using namespace DirectX::SimpleMath;

const int WORLD_WIDTH = 50;		//ワールド（マップ）の横幅
const int WORLD_HEIGHT = 60;		//ワールド（マップ）の縦幅
extern Player* aza;			//外部からプレイヤーをカメラに

//=======================================
//初期化処理
//=======================================
void Camera::Init ( )
{
	m_Position = Vector3 ( 0.0f , 0.0f , -50.0f );
	m_Target = Vector3 ( 0.0f , 0.0f , 0.0f );
}


//=======================================
//更新処理
//=======================================
void Camera::Update ( )
{

	Vector3 player = aza->GetPosition ( );
	//プレイヤーをフォロー
	m_Position.x = aza->GetPosition ( ).x;
	m_Position.y = aza->GetPosition ( ).y;
	m_Target = aza->GetPosition ( );

	//プレイヤーが壁に到着した時処理
	if ( m_Position.x < -WORLD_WIDTH / 2 ) {	//一番左
		m_Position.x = -WORLD_WIDTH / 2;
		m_Target.x = -WORLD_WIDTH / 2;
	}
	if ( m_Position.x > WORLD_WIDTH / 2 ) {	//一番右
		m_Position.x = WORLD_WIDTH / 2;
		m_Target.x = WORLD_WIDTH / 2;
	}
	if ( m_Position.y < 0 ) {	//地面
		m_Position.y = 0;
		m_Target.y = 0;
	}
	if ( m_Position.y > WORLD_HEIGHT / 2 ) {	//一番上
		m_Position.y = WORLD_HEIGHT / 2;
		m_Target.y = WORLD_HEIGHT / 2;
	}
}

//=======================================
//描画処理
//=======================================
void Camera::Draw ( )
{
	// ビュー変換後列作成
	Vector3 up = Vector3 ( 0.0f , 1.0f , 0.0f );
	m_ViewMatrix = DirectX::XMMatrixLookAtLH ( m_Position , m_Target , up ); // 左手系にした　20230511 by suzuki.tomoki
	// DIRECTXTKのメソッドは右手系　20230511 by suzuki.tomoki
	// 右手系にすると３角形頂点が反時計回りになるので描画されなくなるので注意
	// このコードは確認テストのために残す
	// m_ViewMatrix = m_ViewMatrix.CreateLookAt(m_Position, m_Target, up);					

	Renderer::SetViewMatrix ( &m_ViewMatrix );

	//プロジェクション行列の生成
	constexpr float fieldOfView = DirectX::XMConvertToRadians ( 45.0f );    // 視野角

	float aspectRatio = static_cast< float >( Application::GetWidth ( ) ) / static_cast< float >( Application::GetHeight ( ) );	// アスペクト比	
	float nearPlane = 1.0f;       // ニアクリップ
	float farPlane = 1000.0f;      // ファークリップ

	//プロジェクション行列の生成
	Matrix projectionMatrix;
	projectionMatrix = DirectX::XMMatrixPerspectiveFovLH ( fieldOfView , aspectRatio , nearPlane , farPlane );	// 左手系にした　20230511 by suzuki.tomoki
	// DIRECTXTKのメソッドは右手系　20230511 by suzuki.tomoki
	// 右手系にすると３角形頂点が反時計回りになるので描画されなくなるので注意
	// このコードは確認テストのために残す
	// projectionMatrix = DirectX::SimpleMath::Matrix::CreatePerspectiveFieldOfView(fieldOfView, aspectRatio, nearPlane, farPlane);

	Renderer::SetProjectionMatrix ( &projectionMatrix );
}


//=======================================
//終了処理
//=======================================
void Camera::Uninit ( )
{

}

