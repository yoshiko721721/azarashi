#include "GoUI.h"

int GoCountX = 0;
int GoCountY = 0;

void GoUI::Init()
{
	Initialize(L"Asset/pic/Go.png");   //�w�i��������
	SetPos(0.0f, 0.0f, 0.0f);      //�ʒu��ݒ�
	SetSize(0.0f, 0.0f, 0.0f);  //�傫����ݒ�
	SetAngle(0.0f);                //�p�x��ݒ�
	SetColor(1.0f, 1.0f, 1.0f, 1.0f);//�p�x��ݒ�

	GoCountX = 0;
	GoCountY = 0;
}

void GoUI::Update()//�w�i�̃A�b�v�f�[�g(����Ȃ��C������)
{
	if (GoCountX < 1920)
	{
		GoCountX += 16;
		GoCountY += 9;
		SetSize(GoCountX, GoCountY, GetSize().z);
	}
}