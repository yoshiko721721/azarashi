#include "SelectPlayer.h"
void SelectPlayer::Init()
{
	Initialize(L"Asset/pic/Player_Idle.png");   //�w�i��������
	SetPos(-620.0f, 0.0f, 0.0f);      //�ʒu��ݒ�
	SetSize(360.0f, 195.0f, 0.0f);  //�傫����ݒ�
	SetAngle(0.0f);                //�p�x��ݒ�
	SetColor(1.0f, 1.0f, 1.0f, 1.0f);//�p�x��ݒ�
}

void SelectPlayer::Update(int selectStage)//�w�i�̃A�b�v�f�[�g(����Ȃ��C������)
{
	XMFLOAT3 pos = GetPos();


	switch (selectStage)
	{
	case 0:
	{
		pos.x = -580.0f;
		pos.y =   50.0f;
		break;
	}
	case 1:
	{
		pos.x = -200;
		pos.y = -170.0f;
		break;
	}
	case 2:
	{
		pos.x = 200.0f;
		pos.y =   50;
		break;
	}
	case 3:
	{
		pos.x =  580.0f;
		pos.y = -170.0f;
		break;
	}
	case 4:
	{
		pos.x = -710.0f;
		pos.y =  395;
		break;
	}
	default:
		break;
	}


	SetPos(pos.x, pos.y, pos.z);
}