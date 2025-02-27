#include "TitleBackGroundPAB.h"

int titleBackGroundCount = 0;

void TitleBackGroundPAB::Init()
{
	Initialize(L"Asset/pic/Background_Title_PAB.png");   //背景を初期化
	SetPos(0.0f, 0.0f, 0.0f);      //位置を設定
	SetSize(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);  //大きさを設定
	SetAngle(0.0f);                //角度を設定
	SetColor(1.0f, 1.0f, 1.0f, 1.0f);//角度を設定
}

void TitleBackGroundPAB::Update(void)
{
	DirectX::XMFLOAT4 Color = GetColor();
	titleBackGroundCount++;

	if (titleBackGroundCount == 60)
	{
		if (Color.w == 0.5)
		{
			Color.w = 1.0f;
		}
		else if (Color.w == 1)
		{
			Color.w = 0.5f;
		}

		titleBackGroundCount = 0;
	}
	SetColor(Color.x,Color.y,Color.z,Color.w);
}

/*
bool wflg = true;

void TitleBackGroundPAB::Update(void)
{
	DirectX::XMFLOAT4 Color = GetColor();
	titleBackGroundCount++;

	if (titleBackGroundCount == 1)
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
		titleBackGroundCount = 0;
	}
	SetColor(Color.x,Color.y,Color.z,Color.w);
}
*/