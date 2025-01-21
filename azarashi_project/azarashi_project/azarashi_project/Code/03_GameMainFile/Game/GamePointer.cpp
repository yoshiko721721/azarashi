#include "GamePointer.h"
#include "../../03_GameMainFile/Math.h"

using DirectX::XMFLOAT3;

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

void GamePointer::Update(ContactPointVector collision, Object& block)//Playerのアップデート
{

	Vector2 blockPos = { block.GetPos().x, block.GetPos().y };
	now = collision.checkCollision;

	//自由落下
	body.FreeFall(body.GetTime());

	//衝突しているの処理
	if (now)
	{

		body.CalcFainalNormalAngle(collision.closspoint, *this, block);	//法線の角度を計算
		body.HorizonUpdate(block, AZARASHI_MODE[azaNum]);			//転がる処理

		//ジャンプ
		if (Input::GetKeyTrigger(VK_RETURN)) {
			body.AddForce(0.0f, 15.0f);
		}



		body.DampingVector(damping, azaNum);
		body.Repulsion();			//反発

		//座標を補正
		GamePointer::CorrectPosition(&block, collision.closspoint,
			collision.DistanceSquared, block.GetAngle());

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
		case STAND:  Initialize(AZARASHI_PICTURE_STAND);
			SetAngle(block.GetAngle());			  break;
		}
	}

	//当たり判定の記録
	old = now;
	SetPos(GetPos().x + body.GetVector().x, GetPos().y + body.GetVector().y, 0);

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
/// @param distanceSquared 円の中心座標とclossPointの距離の2乗
/// @param angle blockの角度
void GamePointer::CorrectPosition(Object* m_Block, XMFLOAT2 clossPoint, float distanceSquared, float angle)
{
	float distance = sqrt(distanceSquared);				//正式な距離にする
	float overlap = (GetSize().y / 2) - distance;		//円の半径
	XMFLOAT2 direction = { GetPos().x - clossPoint.x, GetPos().y - clossPoint.y };
	float length = sqrt(direction.x * direction.x + direction.y * direction.y);
	direction = { direction.x / length, direction.y / length };


	SetPos(GetPos().x + direction.x * overlap, GetPos().y + direction.y * overlap, 0);
}

