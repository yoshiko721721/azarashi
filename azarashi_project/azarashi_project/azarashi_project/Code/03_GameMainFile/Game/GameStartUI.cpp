#include "GameStartUI.h"

//ID3D11ShaderResourceView* LoadTexture(const wchar_t*);

void GameStartUI::Init()
{
	Initialize(L"Asset/pic/Go.png");   //�w�i��������
	SetPos(0.0f, 0.0f, 0.0f);      //�ʒu��ݒ�
	SetSize(1920.0f, 1080.0f, 0.0f);  //�傫����ݒ�
	SetAngle(0.0f);                //�p�x��ݒ�
	SetColor(1.0f, 1.0f, 1.0f, 1.0f);//�p�x��ݒ�
}

void GameStartUI::Update()//�w�i�̃A�b�v�f�[�g(����Ȃ��C������)
{

}
