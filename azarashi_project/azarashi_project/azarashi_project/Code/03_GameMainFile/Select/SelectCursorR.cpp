#include "SelectCursorR.h"
void SelectCursorR::Init()
{
	Initialize(L"Asset/pic/SelectUI/UI_Cursor_R.png");   //�w�i��������
	SetPos(890.0f, 0.0f, 0.0f);      //�ʒu��ݒ�
	SetSize(97.0f, 198.0f, 0.0f);  //�傫����ݒ�
	SetAngle(0.0f);                //�p�x��ݒ�
	SetColor(1.0f, 1.0f, 1.0f, 1.0f);//�p�x��ݒ�
}

void SelectCursorR::Update(int a)//�w�i�̃A�b�v�f�[�g(����Ȃ��C������)
{
	SetColor(1.0f, 1.0f, 1.0f, a);//�p�x��ݒ�
}