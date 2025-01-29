#include "PauseUI.h"
void PauseUI::Init()
{
	//SetTexture(textures[0]);
	Initialize(L"Asset/pic/UI_Pause.png");   //背景を初期化
	SetPos(0.0f, 0.0f, 0.0f);      //位置を設定
	SetSize(474.0f, 674.0f, 0.0f);  //大きさを設定
	SetAngle(0.0f);                //角度を設定
	SetColor(1.0f, 1.0f, 1.0f, 1.0f);//角度を設定
}

void PauseUI::Update()//背景のアップデート(いらない気がする)
{

}