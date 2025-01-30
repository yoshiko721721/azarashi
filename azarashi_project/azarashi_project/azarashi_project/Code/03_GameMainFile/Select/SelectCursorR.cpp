#include "SelectCursorR.h"
void SelectCursorR::Init()
{
	Initialize(L"Asset/pic/SelectUI/UI_Cursor_R.png");   //背景を初期化
	SetPos(890.0f, 0.0f, 0.0f);      //位置を設定
	SetSize(97.0f, 198.0f, 0.0f);  //大きさを設定
	SetAngle(0.0f);                //角度を設定
	SetColor(1.0f, 1.0f, 1.0f, 1.0f);//角度を設定
}

void SelectCursorR::Update(int a)//背景のアップデート(いらない気がする)
{
	SetColor(1.0f, 1.0f, 1.0f, a);//角度を設定
}