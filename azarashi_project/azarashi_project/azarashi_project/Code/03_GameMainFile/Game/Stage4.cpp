#include "Stage4.h"

//ID3D11ShaderResourceView* LoadTexture(const wchar_t*);

void Stage4::Init()
{
	//SetTexture(textures[0]);
	Initialize(L"Asset/pic/SelectUI/Stageselect_1_4.png");   //�w�i��������
	SetPos(580.0f, -170.0f, 0.0f);      //�ʒu��ݒ�
	SetSize(500.0f, 500.0f, 0.0f);  //�傫����ݒ�
	SetAngle(0.0f);                //�p�x��ݒ�
	SetColor(1.0f, 1.0f, 1.0f, 1.0f);//�p�x��ݒ�
}

void Stage4::Update(int selectPage)//�w�i�̃A�b�v�f�[�g(����Ȃ��C������)
{
	//SetTexture(imgname[selectPage]);
}
