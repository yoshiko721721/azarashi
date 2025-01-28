#include "SelectTitleBackUI.h"
void TitleBackUI::Init()
{
	Initialize(L"Asset/pic/SelectUI/UI_Backtitle.png");   //背景を初期化
	SetPos(-800.0f, 425.0f, 0.0f);      //位置を設定
	SetSize(264.0f, 204.0f, 0.0f);  //大きさを設定
	SetAngle(0.0f);                //角度を設定
	SetColor(1.0f, 1.0f, 1.0f, 1.0f);//角度を設定
}

void TitleBackUI::Update(int selectPage)//のアップデート(いらない気がする)
{
	
}