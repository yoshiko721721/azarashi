#include "Stone.h"
#include "../../../03_GameMainFile/Math.h"
#include "../../../08_Collider/BoxCollider.h"
#include"../../Application.h"
#include<vector>

using DirectX::XMFLOAT3;
const float LIMMIT = 0.1;
const float ROLLINGSPEED = 5.0f;


//=========================================
//				初期化処理
//=========================================
void Stone::Init()
{
	Initialize(L"Asset/pic/Rock1.png");   
	SetSize(100.0f, 100.0f, 0.0f);		  //大きさを設定
	SetAngle(0.0f);						  //角度を設定
	SetColor(1.0f, 1.0f, 1.0f, 1.0f);	  //色を設定

	circle.radius = GetPos().y / 2;

	body.SetMass(7.0f);					  //質量を設定
	body.SetTime(0.01);					  //時間を初期化
	body.SetMag(7.0f);					  //倍率を設定
	body.SetVector(0.0f, 0.0f);

	now = 0;
}

//===========================================
//				更新処理					
//===========================================

void Stone::Update()//Playerのアップデート
{
	std::vector<GameBlock*> blocks = Application::GetInstance()->GetObjects<GameBlock>();
	int hitObj = 0;
	for (auto& block : blocks) {
		collision = BoxCollider::ColliderWithCircle(this, block);
		if (collision.checkCollision != NO_COLLISION) {
			m_Block = block;
			if (hitObj < 2) {
				m_Blocks[hitObj] = block;
				hitObj++;
			}
			NowHitsCounter(1);
		}
	}
	switch (hitObj) {
	case 0: m_Blocks[0] = nullptr;
	case 1: m_Blocks[1] = nullptr;
	}

	//自由落下
	if (now < 1 && behavior == BOUND) {
		body.FreeFall(body.GetTime());
	}


	//衝突しているの処理
	if (now == 1)
	{
		body.CalcFinalNormalAngle(collision, *this, *m_Block);	//法線の角度を計算

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
			body.HorizonUpdate(*this, *m_Block, Stone_Friction, ROLLINGSPEED);			//転がる処理
			break;
		}

		//ジャンプ
		if (Input::GetKeyTrigger(VK_RETURN)) {
			body.AddForce(0.0f, 35.0f);
			behavior = BOUND;
		}

		//座標を補正
		CorrectPosition(*m_Block, collision, m_Block->GetAngle());

	}
	else {
		behavior = BOUND;
	}


	//一回前の当たり判定を記憶
	oldVectorNum = body.vectorNum;
	SetPos(GetPos().x + body.GetVector().x, GetPos().y + body.GetVector().y, 0);
}

float Stone::GetCircleRadius()
{
	return circle.radius;
}

float Stone::GetFrictionResistance()
{
	return Stone_Friction;
}

//横に転がった分だけ回転する
void Stone::RotateTexture()  //引数　：　当たった物体の摩擦抵抗
{
	float tempAngle = GetAngle();

	if (body.GetVector().x < 0)
		tempAngle -= body.GetVector().x + Stone_Friction;
	else if (body.GetVector().x > 0)
		tempAngle -= body.GetVector().x + Stone_Friction;

	tempAngle -= body.vector.x;

	SetAngle(tempAngle);
}

/// @brief 座標の補正
/// @param m_Block	当たったブロックの引数
/// @param clossPoint 円と四角形の接地点
/// @param distanceSquared 円の中心座標とclossPointの距離 
/// @param angle blockの角度
void Stone::CorrectPosition(Object& block, ContactPointVector collision, float angle)
{
	// 正式な距離を計算
	float distance = sqrt(collision.distanceSquared);
	// 円の重なり距離を計算
	float overlap = (GetSize().y / 2) - distance;
	// ブロックの回転角度に基づく法線の計算
	XMFLOAT2 blockNormal = {
		cos(body.GetFinalAngle()),
		sin(body.GetFinalAngle())
	};
	cout << "法線ベクトル = " << Math::ConvertToDegree(body.GetFinalAngle()) << "\n";

	SetPos(GetPos().x + blockNormal.x * overlap, GetPos().y + blockNormal.y * overlap, 0);

}

int Stone::GetNowHits()
{
	return now;
}

void Stone::NowHitsCounter(int count)
{
	now += count;
}

Object* Stone::GetHitGameBlock(int objCount)
{
	if (objCount < 2) {
		return m_Blocks[objCount];
	}
	return nullptr;
}
