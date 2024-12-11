#include "GamePointer.h"
#include "../../03_GameMainFile/Math.h"

using DirectX::XMFLOAT3 ;

//=========================================
//				初期化処理
//=========================================
void GamePointer::Init()
{
	Initialize(AZARASHI_PICTURE_STAND);   //背景を初期化
	SetPos(   0.0f,   0.0f, 0.0f);		  //位置を設定
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

void GamePointer::Update(float blockAngle)//Playerのアップデート
{
	Vector2 pos = { GetPos().x,GetPos().y };

	body.TimeCounter(FRAMERATE);
	body.Update(pos, body.GetTime());		//時間を引数にして物理の更新処理

	


	pos.x += body.GetVector().x;			//
	pos.y += body.GetVector().y;			//最後に位置を移動した分更新

	SetPos(pos.x, pos.y, 0);
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
		tempAngle -= body.GetVector().x + AZARASHI_MODE[azaNum] ;
	else if (body.GetVector().x > 0)
		tempAngle -= body.GetVector().x + AZARASHI_MODE[azaNum] ;

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

