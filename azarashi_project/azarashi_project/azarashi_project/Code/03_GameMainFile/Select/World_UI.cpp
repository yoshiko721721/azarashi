#include "World_UI.h"
void WorldUI::Init()
{
	Initialize(imgname[0]);   //�w�i��������
	SetPos(-240.0f, 400.0f, 0.0f);      //�ʒu��ݒ�
	SetSize(364.0f, 304.0f, 0.0f);  //�傫����ݒ�
	SetAngle(0.0f);                //�p�x��ݒ�
	SetColor(1.0f, 1.0f, 1.0f, 1.0f);//�p�x��ݒ�
}

void WorldUI::Update(int selectPage)//�w�i�̃A�b�v�f�[�g(����Ȃ��C������)
{
	SetTexture(imgname[selectPage]); 
}