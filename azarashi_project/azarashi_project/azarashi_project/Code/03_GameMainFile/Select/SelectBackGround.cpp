#include "SelectBackGround.h"

void SelectBackGround::Init()
{
	Initialize(L"Asset/pic/Title_BackGround.png");   //�w�i��������
	SetPos(0.0f, 0.0f, 0.0f);      //�ʒu��ݒ�
	SetSize(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);  //�傫����ݒ�
	SetAngle(0.0f);                //�p�x��ݒ�
	SetColor(1.0f, 1.0f, 1.0f, 1.0f);//�p�x��ݒ�
}

void SelectBackGround::Update(void)
{
	DirectX::XMFLOAT3 pos = GetPos();
	SetPos(pos.x, pos.y, pos.z);
}