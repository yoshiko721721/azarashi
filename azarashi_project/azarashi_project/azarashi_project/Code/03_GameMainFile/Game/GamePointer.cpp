#include "GamePointer.h"
#include "../../03_GameMainFile/Math.h"
#include "../../08_Collider/BoxCollider.h"
#include"../Application.h"
#include<vector>

using DirectX::XMFLOAT3;
const float LIMMIT = 0.1;
const float ROLLINGSPEED = 5.0f;


//=========================================
//				初期化処理
//=========================================
void GamePointer::Init()
{
	Initialize(AZARASHI_PICTURE_STAND);   //背景を初期化
	SetPos(0.0f, 0.0f, 0.0f);		  //位置を設定
	SetSize(100.0f, 100.0f, 0.0f);		  //大きさを設定
	SetAngle(0.0f);						  //角度を設定
	SetColor(1.0f, 1.0f, 1.0f, 1.0f);	  //色を設定

	circle.radius = GetPos().y / 2;

	body.SetMass(7.0f);					  //質量を設定
	body.SetTime(0.01);					  //時間を初期化
	body.SetMag(7.0f);					  //倍率を設定
	body.SetVector(0.0f, 0.0f);

}

//===========================================
//				更新処理					
//===========================================

void GamePointer::Update()//Playerのアップデート
{
	std::vector<GameBlock*> blocks = Application::GetInstance()->GetObjects<GameBlock>();
	for (auto& block : blocks) {
		collision = BoxCollider::ColliderWithCircle(this, block);
		if ( collision.checkCollision) {
			now = collision.checkCollision;
			m_Block = block;
			break;
		}
	}

	//自由落下
	if (!now && behavior == BOUND) {
		body.FreeFall(body.GetTime());
	}


	//衝突しているの処理
	if (now)
	{
		body.CalcFainalNormalAngle(collision.closspoint, *this, *m_Block);	//法線の角度を計算

		switch (behavior) {
		case BOUND:
			body.Repulsion();			//反発
			if ((oldVectorNum - body.vectorNum) < LIMMIT && (oldVectorNum - body.vectorNum) > -LIMMIT) {
				behavior = ROLLING;
				body.vector.x = 0;
				body.vector.y = 0;
			}
			break;
		case ROLLING:
			body.HorizonUpdate(AZARASHI_MODE[azaNum], ROLLINGSPEED);			//転がる処理
			break;
		}

		//ジャンプ
		if (Input::GetKeyTrigger(VK_RETURN)) {
			body.AddForce(0.0f, 10.0f);
			behavior = BOUND;
		}
		//body.DampingVector(damping, azaNum);

		//座標を補正
		CorrectPosition(m_Block, collision.closspoint,collision.DistanceSquared);
	}
	else {
		behavior = BOUND;
		now = false;
	}

	//モード切り替え
	if (Input::GetKeyPress(VK_T)) {
		SetAzaNum(CIRCLE);
	}
	else {
		SetAzaNum(STAND);
	}

	//モードチェンジ
	if (isChangeMode()) {
		switch (azaNum) {
		case CIRCLE: Initialize(AZARASHI_PICTURE_CIRCLE); break;
		case STAND:  Initialize(AZARASHI_PICTURE_STAND);  break;
		}
	}

	//一回前のベクトルを記憶
	oldVectorNum = body.vectorNum;
	SetPos(GetPos().x + body.GetVector().x, GetPos().y + body.GetVector().y, 0);

	//std::cout << "now = " << now << std::endl ;

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
void GamePointer::RotateTexture(const float sub)  //引数　：　当たった物体の摩擦抵抗
{
	float tempAngle = GetAngle();

	if (body.GetVector().x < 0)
		tempAngle -= body.GetVector().x + AZARASHI_MODE[azaNum];
	else if (body.GetVector().x > 0)
		tempAngle -= body.GetVector().x + AZARASHI_MODE[azaNum];

	tempAngle -= body.vector.x;

	SetAngle(tempAngle);
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
void GamePointer::CorrectPosition(Object* m_Block, XMFLOAT2 clossPoint, float distanceSquared)
{
	// 正式な距離を計算
	float distance = sqrt(distanceSquared);

	// 円の重なり距離を計算
	float overlap = (GetSize().y / 2) - distance;

	// 四角形の法線を計算（角度を考慮）
	// ブロックの回転角度に基づく法線の計算
	XMFLOAT2 blockNormal = {
		cos(body.fainalNormalAngle),
		sin(body.fainalNormalAngle)
	};

	// 接点から円の中心へのベクトルを計算
	XMFLOAT2 direction = { GetPos().x - clossPoint.x, GetPos().y - clossPoint.y };
	float length = sqrt(direction.x * direction.x + direction.y * direction.y);

	if (length > 0.0f) {
		direction = { direction.x / length, direction.y / length };
	}

	// 法線方向との内積を計算して補正方向を調整
	float dotProduct = direction.x * blockNormal.x + direction.y * blockNormal.y;
	if (dotProduct < 0) {
		blockNormal = { -blockNormal.x, -blockNormal.y };
	}

	// 補正を適用
	SetPos(GetPos().x + blockNormal.x * overlap, GetPos().y + blockNormal.y * overlap, 0);
}
