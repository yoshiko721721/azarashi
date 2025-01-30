#include "GameBlock_stop.h"
#include "../../../03_GameMainFile/Application.h" 
#include <DirectXMath.h>

extern float gyroData[3]; // x, y, z²

void GameBlock_stop::Init()
{
	Initialize(L"Asset/pic/Box.png");   //”wŒi‚ğ‰Šú‰»
	//SetPos(groundX, groundY, 0.0f);      //ˆÊ’u‚ğİ’è
	//SetSize(600.0f, 50.0f, 0.0f);  //‘å‚«‚³‚ğİ’è
	SetAngle(0.0f);                //Šp“x‚ğİ’è
	SetColor(1.0f, 1.0f, 1.0f, 1.0f);//F‚ğİ’è
}

void GameBlock_stop::Update()
{
   
}





