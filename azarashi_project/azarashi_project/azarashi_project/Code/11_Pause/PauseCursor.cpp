#include "PauseCursor.h"
void PauseCursor::Init()
{
	//SetTexture(textures[0]);
	Initialize(L"Asset/pic/PauseCursor.png");   //�w�i��������
	SetPos(0.0f, 0.0f, 0.0f);      //�ʒu��ݒ�
	SetSize(200.0f, 200.0f, 0.0f);  //�傫����ݒ�
	SetAngle(0.0f);                //�p�x��ݒ�
	SetColor(1.0f, 1.0f, 1.0f, 1.0f);//�p�x��ݒ�
}

void PauseCursor::Update()//�w�i�̃A�b�v�f�[�g(����Ȃ��C������)
{

}