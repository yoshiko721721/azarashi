#include "PauseCursor.h"
void PauseCursor::Init()
{
	//SetTexture(textures[0]);
	Initialize(L"Asset/pic/PauseCursor.png");   //背景を初期化
	SetPos(0.0f, 0.0f, 0.0f);      //位置を設定
	SetSize(200.0f, 200.0f, 0.0f);  //大きさを設定
	SetAngle(0.0f);                //角度を設定
	SetColor(1.0f, 1.0f, 1.0f, 1.0f);//角度を設定
}

void PauseCursor::Update()//背景のアップデート(いらない気がする)
{

}