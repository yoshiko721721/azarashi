#include "World_UI.h"
void WorldUI::Init()
{
	Initialize(imgname[0]);   //背景を初期化
	SetPos(-240.0f, 400.0f, 0.0f);      //位置を設定
	SetSize(364.0f, 304.0f, 0.0f);  //大きさを設定
	SetAngle(0.0f);                //角度を設定
	SetColor(1.0f, 1.0f, 1.0f, 1.0f);//角度を設定
}

void WorldUI::Update(int selectPage)//背景のアップデート(いらない気がする)
{
	SetTexture(imgname[selectPage]); 
}