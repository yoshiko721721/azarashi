#include "GamePointer.h"
#include "../../03_GameMainFile/Math.h"
#include "../../08_Collider/BoxCollider.h"
#include "../../07_Camera/Camera.h"
#include"../Application.h"
#include<vector>

using DirectX::XMFLOAT3;
const float LIMMIT = 0.1;
const float ROLLINGSPEED = 5.0f;

extern Sound sound;

//=========================================
//				初期化処理
//=========================================
void GamePointer::Init()
{
	Initialize(AZARASHI_PICTURE_STAND);   //背景を初期化
	//SetPos(0.0f, 0.0f, 0.0f);		  //位置を設定
	//SetSize(100.0f, 100.0f, 0.0f);		  //大きさを設定
	SetAngle(0.0f);						  //角度を設定
	SetColor(1.0f, 1.0f, 1.0f, 1.0f);	  //色を設定
	SetSize(SIZE_POINTER_STAND, SIZE_POINTER_CIRCLE, 0.0f);
	circle.radius = GetPos().y / 2;

	body.SetMass(7.0f);					  //質量を設定
	body.SetTime(0.01);					  //時間を初期化
	body.SetMag(7.0f);					  //倍率を設定
	body.SetVector(0.0f, 0.0f);

	textures[CIRCLE] = LoadTexture(AZARASHI_PICTURE_CIRCLE);
	textures[STAND]  = LoadTexture(AZARASHI_PICTURE_STAND);
	
		now = 0;
}

//===========================================
//				更新処理					
//===========================================

void GamePointer::Update()//Playerのアップデート
{
	//Camera::UnLock();
	Controller::Input::Update();
	std::vector<GameBlock*> blocks = Application::GetInstance()->GetObjects<GameBlock>();
	int hitObj = 0;
	float nrmAngle = 0.0f;
	float distance = 0.0f;
	for (auto& block : blocks) {
		collision = BoxCollider::ColliderWithCircle(this, block);
		if (collision.checkCollision != NO_COLLISION) {
			m_Block = block;
			myCollision = collision;
			distance += collision.distanceSquared;
			nrmAngle += body.CalcFinalNormalAngle(myCollision, *this, *block);	//法線の角度を計算
			if (hitObj < 4) {
				m_Blocks[hitObj] = block;
				hitObj++;
			}
			NowHitsCounter(1);
		}
	}


	//自由落下
	if (hitObj == 0 && behavior == BOUND) {
		body.FreeFall(body.GetTime());
	}
	else if (hitObj > 0) {
		//座標を補正
		nrmAngle /= (float)hitObj;
		distance /= (float)hitObj;
		CorrectPosition(*m_Block, distance, nrmAngle);

	}


	//衝突しているの処理
	if (now == 1)
	{
		
		if (m_Block != nullptr)
		{

			

			if (behavior == ROLLING || boundCounter >= 4) {
				body.HorizonUpdate(*this, *m_Block, AZARASHI_MODE[azaNum], ROLLINGSPEED);			//転がる処理
			}
			else {
				boundCounter++;
				body.Repulsion();			//反発
			}
			

			//ジャンプ
			if (Input::GetKeyTrigger(VK_RETURN) || Input::GetButtonTrigger(XINPUT_A)) 
			{
				sound.Play(SOUND_LABEL_SE4);
				PointerJump(myCollision.closspoint.normalAngle);
				behavior = BOUND;
				boundCounter = 0;
			}


		}
	}
	else {
		behavior = BOUND;
	}


	//モード切り替え
	if ((Controller::Input::GetLeftTrigger()   > 0 && Controller::Input::GetLeftTrigger() <= 1) &&
		(Controller::Input::GetRightTrigger() >= 0 && Controller::Input::GetRightTrigger() <= 1) || 
		Input::GetKeyPress(VK_T))
	{
		SetAzaNum(CIRCLE);
	}
	else 
	{
		SetAzaNum(STAND);
	}
	//モードチェンジ
	if (isChangeMode()) {
		switch (azaNum) {
		case CIRCLE: m_pTextureView = textures[CIRCLE]; 
					 SetSize(SIZE_POINTER_CIRCLE, SIZE_POINTER_CIRCLE, 0.0f);
			break;
		case STAND:  m_pTextureView = textures[STAND];  
					 float standAngle = myCollision.closspoint.normalAngle - 90.0f;
					 SetSize(SIZE_POINTER_STAND, SIZE_POINTER_CIRCLE, 0.0f);
					 SetAngle(standAngle);
			break;
		}
	}
	//横移動と連動した画像の回転
	if (azaNum == CIRCLE) {
		RotateTexture();
	}


	//一回前の当たり判定を記憶
	oldVectorNum = Math::CalcSquareRoot(body.GetVector().x, body.GetVector().y);
	SetPos(GetPos().x + body.GetVector().x, GetPos().y + body.GetVector().y, 0);
	now = 0;
}

float GamePointer::GetCircleRadius()
{
	return circle.radius;
}

float GamePointer::GetFrictionResistance()
{
	return AZARASHI_MODE[azaNum];
}

//横に転がった分だけ回転する
void GamePointer::RotateTexture()  //引数　：　当たった物体の摩擦抵抗
{
	float tempAngle = GetAngle();

	if (body.GetVector().x < 0)
		tempAngle -= body.GetVector().x / 10.0f + AZARASHI_MODE[azaNum];
	else if (body.GetVector().x > 0)
		tempAngle -= body.GetVector().x / 10.0f + AZARASHI_MODE[azaNum];

	tempAngle -= body.vector.x;

	SetAngle(tempAngle);
}

void GamePointer::PointerJump(float angle)
{
	Radian forceAngle = Math::ConvertToRadian(angle);
	body.vectorNum = FORCE_JUMP;
	Vector2 force = { body.vectorNum * cos(forceAngle),
					  body.vectorNum * sin(forceAngle)};
	
	body.AddForce(force.x, force.y);
}

ID3D11ShaderResourceView* GamePointer::LoadTexture(const wchar_t* filename)
{
	HRESULT hr = DirectX::CreateWICTextureFromFile(g_pDevice, filename, NULL, &m_pTextureView);
	if (FAILED(hr))
	{
		MessageBoxA(NULL, "テクスチャ読み込み失敗", "エラー", MB_ICONERROR | MB_OK);
	}
	return m_pTextureView;
}



bool GamePointer::isChangeMode()
{
	if (azaNum != oldAzaNum) {
		return true;
	}
	return false;
}

void GamePointer::SetAzaNum(AZA_MODE_NUMMBER m_AzaNum)
{
	oldAzaNum = azaNum;
	azaNum = m_AzaNum;
}

/// @brief 座標の補正
/// @param m_Block	当たったブロックの引数
/// @param clossPoint 円と四角形の接地点
/// @param distanceSquared 円の中心座標とclossPointの距離 
/// @param angle blockの角度
void GamePointer::CorrectPosition(Object& block, float distancesqured, float angle)
{
	// 正式な距離を計算
	float distance = sqrt(distancesqured);
	// 円の重なり距離を計算
	float overlap = (GetSize().y / 2.0f) - distance;
	// ブロックの回転角度に基づく法線の計算
	XMFLOAT2 blockNormal = {
		cos(angle) * overlap,
		sin(angle) * overlap
	};
	SetPos(GetPos().x + blockNormal.x , GetPos().y + blockNormal.y , 0.0f);

}

int GamePointer::GetNowHits()
{
	return now;
}

void GamePointer::NowHitsCounter(int count)
{
	now += count;
}

Object* GamePointer::GetHitGameBlock(int objCount)
{
	if (objCount < 2) {
		return m_Blocks[objCount];
	}
	return nullptr;
}
