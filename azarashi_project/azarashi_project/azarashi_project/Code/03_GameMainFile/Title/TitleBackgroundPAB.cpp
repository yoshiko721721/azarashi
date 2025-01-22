#include "TitleBackGroundPAB.h"

int titleBackGroundCount = 0;

void TitleBackGroundPAB::Init()
{
	Initialize(L"Asset/pic/Background_Title_PAB.png");   //”wŒi‚ğ‰Šú‰»
	SetPos(0.0f, 0.0f, 0.0f);      //ˆÊ’u‚ğİ’è
	SetSize(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);  //‘å‚«‚³‚ğİ’è
	SetAngle(0.0f);                //Šp“x‚ğİ’è
	SetColor(1.0f, 1.0f, 1.0f, 1.0f);//Šp“x‚ğİ’è
}

void TitleBackGroundPAB::Update(void)
{
	DirectX::XMFLOAT4 Color = GetColor();
	titleBackGroundCount++;

	if (titleBackGroundCount == 120)
	{
		if (Color.w == 0)
		{
			Color.w = 1.0f;
		}
		else if (Color.w == 1)
		{
			Color.w = 0.0f;
		}

		titleBackGroundCount = 0;
	}
	SetColor(Color.x,Color.y,Color.z,Color.w);
}
