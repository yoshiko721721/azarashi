#include "GameBlock.h"
void GameBlock::Init()
{
	Initialize(L"asset/Box.png");   //�w�i��������
	SetPos(groundX, groundY, 0.0f);      //�ʒu��ݒ�
	SetSize(600.0f, 50.0f, 0.0f);  //�傫����ݒ�
	SetAngle(0.0f);                //�p�x��ݒ�
	SetColor(1.0f, 1.0f, 1.0f, 1.0f);//�p�x��ݒ�
}

void GameBlock::Update(void)//����̃A�b�v�f�[�g
{
	input.Update();
	DirectX::XMFLOAT3 pos = GetPos();
	angle = GetAngle();
	SetPos(pos.x, pos.y, pos.z);
	SetAngle(angle);
}