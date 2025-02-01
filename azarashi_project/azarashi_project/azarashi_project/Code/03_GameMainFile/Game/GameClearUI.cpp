#include "GameClearUI.h"

//ID3D11ShaderResourceView* LoadTexture(const wchar_t*);

int ClearCountX = 0;
int ClearCountY = 0;

void GameClearUI::Init()
{
	Initialize(L"Asset/pic/Clear.png");   //�w�i��������
	SetPos(0.0f, 0.0f, 0.0f);      //�ʒu��ݒ�
	SetSize(0.0f, 0.0f, 0.0f);  //�傫����ݒ�
	SetAngle(0.0f);                //�p�x��ݒ�
	SetColor(1.0f, 1.0f, 1.0f, 1.0f);//�p�x��ݒ�

	ClearCountX = 0;
	ClearCountY = 0;
}

void GameClearUI::Update()//�w�i�̃A�b�v�f�[�g(����Ȃ��C������)
{
	if (ClearCountX < 1920)
	{
		ClearCountX += 16;
		ClearCountY += 9;
		SetSize(ClearCountX, ClearCountY, GetSize().z);
	}
}
