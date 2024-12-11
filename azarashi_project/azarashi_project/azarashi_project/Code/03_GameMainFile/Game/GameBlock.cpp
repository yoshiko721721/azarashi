#include "GameBlock.h"
void GameBlock::Init()
{
	Initialize(L"Asset/pic/Box.png");   //�w�i��������
	SetPos(groundX, groundY, 0.0f);      //�ʒu��ݒ�
	SetSize(600.0f, 50.0f, 0.0f);  //�傫����ݒ�
	SetAngle(90.0f);                //�p�x��ݒ�
	SetColor(1.0f, 1.0f, 1.0f, 1.0f);//�p�x��ݒ�
}

void GameBlock::Update(void)//����̃A�b�v�f�[�g
{
	if (Input::GetKeyPress(VK_LEFT)) {
		SetAngle(GetAngle() + 3);
	}
	else if (Input::GetKeyPress(VK_RIGHT)) {
		SetAngle(GetAngle() - 3);
	}
	else if (Input::GetKeyPress(VK_SPACE)) {
		SetAngle(0);
	}
}

float GameBlock::GetFrictionRasistance()
{
	return frictionRasistance;
}
