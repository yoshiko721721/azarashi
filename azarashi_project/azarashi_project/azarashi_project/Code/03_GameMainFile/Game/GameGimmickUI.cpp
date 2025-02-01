#include "Gimmick/GameGimmickUI.h"

void GameGimmickUI::Init()
{
	Initialize(L"Asset/pic/Button.png");   //背景を初期化
	SetPos(0.0f, 0.0f, 0.0f);      //位置を設定
	SetSize(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);  //大きさを設定
	SetAngle(0.0f);                //角度を設定
	SetColor(1.0f, 1.0f, 1.0f, 1.0f);//角度を設定
}

void GameGimmickUI::Update()//背景のアップデート(いらない気がする)
{

}