#include "GameBackGround.h"
void GameBackground::Init()
{
	Initialize(L"asset/char02.png");   //�w�i��������
	SetPos(-200.0f, 200.0f, 0.0f);      //�ʒu��ݒ�
	SetSize(100.0f, 100.0f, 0.0f);  //�傫����ݒ�
	SetAngle(0.0f);                //�p�x��ݒ�
	SetColor(1.0f, 1.0f, 1.0f, 1.0f);//�p�x��ݒ�

}

void GameBackground::Update(void)//�w�i�̃A�b�v�f�[�g(����Ȃ��C������)
{
	input.Update();
	DirectX::XMFLOAT3 pos = GetPos();
	SetPos(pos.x, pos.y, pos.z);
}