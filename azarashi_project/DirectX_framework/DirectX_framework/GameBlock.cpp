#include "GameBlock.h"
void GameBlock::Init()
{
	Initialize(L"asset/Box.png");   //背景を初期化
	SetPos(groundX, groundY, 0.0f);      //位置を設定
	SetSize(600.0f, 50.0f, 0.0f);  //大きさを設定
	SetAngle(0.0f);                //角度を設定
	SetColor(1.0f, 1.0f, 1.0f, 1.0f);//角度を設定
}

void GameBlock::Update(void)//足場のアップデート
{
	input.Update();
	DirectX::XMFLOAT3 pos = GetPos();
	angle = GetAngle();
	SetPos(pos.x, pos.y, pos.z);
	SetAngle(angle);
}