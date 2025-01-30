#include "LoadBackgroundPAB.h"

int loadBackGroundCount = 0;

void LoadBackGroundPAB::Init()
{
	Initialize(L"Asset/pic/Background_Load_PAB.png");   //”wŒi‚ğ‰Šú‰»
	SetPos(0.0f, 30.0f, 0.0f);      //ˆÊ’u‚ğİ’è
	SetSize(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);  //‘å‚«‚³‚ğİ’è
	SetAngle(0.0f);                //Šp“x‚ğİ’è
	SetColor(1.0f, 1.0f, 1.0f, 1.0f);//Šp“x‚ğİ’è
}

void LoadBackGroundPAB::Update(void)
{
	DirectX::XMFLOAT4 Color = GetColor();
	loadBackGroundCount++;

	if (loadBackGroundCount == 60)
	{
		if (Color.w == 0.5)
		{
			Color.w = 1.0f;
		}
		else if (Color.w == 1)
		{
			Color.w = 0.5f;
		}

		loadBackGroundCount = 0;
	}
	SetColor(Color.x, Color.y, Color.z, Color.w);
}

/*
bool wflg = true;

void LoadBackGroundPAB::Update(void)
{
	DirectX::XMFLOAT4 Color = GetColor();
	loadBackGroundCount++;

	if (loadBackGroundCount == 1)
	{
		if (Color.w <= 0.5)
		{
			wflg = true;
		}
		else if (Color.w >= 1)
		{
			wflg = false;
		}
		if (wflg == true) {
			Color.w += 0.01;
		}
		else if(wflg == false)
		{
			Color.w -= 0.01;
		}
		loadBackGroundCount = 0;
	}
	SetColor(Color.x,Color.y,Color.z,Color.w);
}
*/