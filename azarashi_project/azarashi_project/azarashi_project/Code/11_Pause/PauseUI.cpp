#include "PauseUI.h"
void PauseUI::Init()
{
	//SetTexture(textures[0]);
	Initialize(L"Asset/pic/UI_Pause.png");   //�w�i��������
	SetPos(0.0f, 0.0f, 0.0f);      //�ʒu��ݒ�
	SetSize(474.0f, 674.0f, 0.0f);  //�傫����ݒ�
	SetAngle(0.0f);                //�p�x��ݒ�
	SetColor(1.0f, 1.0f, 1.0f, 1.0f);//�p�x��ݒ�
}

void PauseUI::Update()//�w�i�̃A�b�v�f�[�g(����Ȃ��C������)
{

}