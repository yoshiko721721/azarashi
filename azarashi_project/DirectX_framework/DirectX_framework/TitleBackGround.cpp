#include "TitleBackGround.h"
void TitleBackground::Init()
{
	Initialize(L"asset/Title_BackGround.png");   //”wŒi‚ğ‰Šú‰»
	SetPos(0.0f, 0.0f, 0.0f);      //ˆÊ’u‚ğİ’è
	SetSize(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);  //‘å‚«‚³‚ğİ’è
	SetAngle(0.0f);                //Šp“x‚ğİ’è
	SetColor(1.0f, 1.0f, 1.0f, 1.0f);//Šp“x‚ğİ’è
}

void TitleBackground::Update(void)
{
	input.Update();
	DirectX::XMFLOAT3 pos = GetPos();
	if (input.GetKeyPress(VK_W))
	{
		pos.x -= 5.0f;
	}
	if (input.GetKeyTrigger(VK_E))
	{
		pos.x += 5.0f;
	}
	SetPos(pos.x, pos.y, pos.z);
}
