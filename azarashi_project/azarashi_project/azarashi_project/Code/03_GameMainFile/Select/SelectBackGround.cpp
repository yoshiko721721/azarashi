#include "SelectBackGround.h"

void SelectBackGround::Init()
{
	Initialize(L"Asset/pic/Title_BackGround.png");   //”wŒi‚ğ‰Šú‰»
	SetPos(0.0f, 0.0f, 0.0f);      //ˆÊ’u‚ğİ’è
	SetSize(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);  //‘å‚«‚³‚ğİ’è
	SetAngle(0.0f);                //Šp“x‚ğİ’è
	SetColor(1.0f, 1.0f, 1.0f, 1.0f);//Šp“x‚ğİ’è
}

void SelectBackGround::Update(void)
{
	DirectX::XMFLOAT3 pos = GetPos();
	SetPos(pos.x, pos.y, pos.z);
}