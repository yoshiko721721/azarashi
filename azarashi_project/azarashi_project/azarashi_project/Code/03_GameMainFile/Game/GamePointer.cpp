#include "GamePointer.h"
using DirectX::XMFLOAT3 ;
void GamePointer::Init()
{
	Initialize(L"Asset/pic/point.png");   //背景を初期化
	SetPos(-250.0f, 100.0f, 0.0f);			  //位置を設定
	SetSize(100.0f, 100.0f, 0.0f);		  //大きさを設定
	SetAngle(0.0f);						  //角度を設定
	SetColor(1.0f, 1.0f, 1.0f, 1.0f);	  //色を設定

	circle.radius = GetPos().y / 2;
	body.SetMass(7.0f);					  //質量を設定
	body.SetTime(0.0f);					  //時間を初期化
	body.SetMag (7.0f);				  //倍率を設定
	body.SetVector(0.0f,0.0f);


}

/// @brief 更新
/// @param  なし
void GamePointer::Update(void)//Playerのアップデート
{
	
	Vector2 pos = { GetPos().x,GetPos().y};
	
	body.TimeCounter(FRAMERATE);			//時間を1 / FPS 計算
	body.Update(pos,body.GetTime());
	
	pos.x += body.GetVector().x;
	pos.y += body.GetVector().y;

	SetPos(pos.x, pos.y, 0);
}

float GamePointer::GetCircleRadius()
{
	return circle.radius;
}

float GamePointer::GetFrictionResistance()
{
	return frictionResistance;
}

void GamePointer::RotateTexture(const float sub)  //引数　：　当たった物体の摩擦抵抗
{
	float tempAngle = GetAngle();

	if (body.GetVector().x < 0)
		tempAngle -= body.GetVector().x + frictionResistance * sub;
	else if (body.GetVector().x > 0)
		tempAngle -= body.GetVector().x + frictionResistance * sub;

	SetAngle( tempAngle);



}




