#include "GameBlock_stop.h"
#include "../../../03_GameMainFile/Application.h" 
#include <DirectXMath.h>

extern float gyroData[3]; // x, y, z軸

void GameBlock_stop::Init()
{
	Initialize(L"Asset/pic/Box.png");   //背景を初期化
	//SetPos(groundX, groundY, 0.0f);      //位置を設定
	//SetSize(600.0f, 50.0f, 0.0f);  //大きさを設定
	SetAngle(0.0f);                //角度を設定
	SetColor(1.0f, 1.0f, 1.0f, 1.0f);//色を設定
}

void GameBlock_stop::Update()
{
   
}





