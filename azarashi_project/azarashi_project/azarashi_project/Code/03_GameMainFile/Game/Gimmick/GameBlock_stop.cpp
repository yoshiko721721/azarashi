#include "GameBlock_stop.h"
#include "../../../03_GameMainFile/Application.h" 
#include <DirectXMath.h>

extern float gyroData[3]; // x, y, z��

void GameBlock_stop::Init()
{
	Initialize(L"Asset/pic/Box.png");   //�w�i��������
	//SetPos(groundX, groundY, 0.0f);      //�ʒu��ݒ�
	//SetSize(600.0f, 50.0f, 0.0f);  //�傫����ݒ�
	SetAngle(0.0f);                //�p�x��ݒ�
	SetColor(1.0f, 1.0f, 1.0f, 1.0f);//�F��ݒ�
}

void GameBlock_stop::Update()
{
   
}





