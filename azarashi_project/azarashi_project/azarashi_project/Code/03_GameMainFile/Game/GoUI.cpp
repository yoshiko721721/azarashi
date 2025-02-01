#include "GoUI.h"

int GoCountX = 0;
int GoCountY = 0;

void GoUI::Init()
{
	Initialize(L"Asset/pic/Go.png");   //背景を初期化
	SetPos(0.0f, 0.0f, 0.0f);      //位置を設定
	SetSize(0.0f, 0.0f, 0.0f);  //大きさを設定
	SetAngle(0.0f);                //角度を設定
	SetColor(1.0f, 1.0f, 1.0f, 1.0f);//角度を設定

	GoCountX = 0;
	GoCountY = 0;
}

void GoUI::Update()//背景のアップデート(いらない気がする)
{
	if (GoCountX < 1920)
	{
		GoCountX += 16;
		GoCountY += 9;
		SetSize(GoCountX, GoCountY, GetSize().z);
	}
}