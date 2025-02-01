#include "GameClearUI.h"

//ID3D11ShaderResourceView* LoadTexture(const wchar_t*);

int ClearCountX = 0;
int ClearCountY = 0;

void GameClearUI::Init()
{
	Initialize(L"Asset/pic/Clear.png");   //背景を初期化
	SetPos(0.0f, 0.0f, 0.0f);      //位置を設定
	SetSize(0.0f, 0.0f, 0.0f);  //大きさを設定
	SetAngle(0.0f);                //角度を設定
	SetColor(1.0f, 1.0f, 1.0f, 1.0f);//角度を設定

	ClearCountX = 0;
	ClearCountY = 0;
}

void GameClearUI::Update()//背景のアップデート(いらない気がする)
{
	if (ClearCountX < 1920)
	{
		ClearCountX += 16;
		ClearCountY += 9;
		SetSize(ClearCountX, ClearCountY, GetSize().z);
	}
}
