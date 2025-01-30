#include "PauseCursor.h"
void PauseCursor::Init()
{
	//SetTexture(textures[0]);
	Initialize(L"Asset/pic/PauseCursor.png");   //�w�i��������
	SetPos(-373.0f, 0.0f, 0.0f);      //�ʒu��ݒ�
	SetSize(200.0f, 200.0f, 0.0f);  //�傫����ݒ�
	SetAngle(0.0f);                //�p�x��ݒ�
	SetColor(1.0f, 1.0f, 1.0f, 1.0f);//�p�x��ݒ�
}

void PauseCursor::Update(bool pause)//�w�i�̃A�b�v�f�[�g(����Ȃ��C������)
{
	if(pause)
	{
		if (Input::GetButtonTrigger(XINPUT_UP) || Input::GetKeyTrigger(VK_W))
		{
			DirectX::XMFLOAT3 pos = GetPos();
			if (pos.y < 300)
			{
				SetPos(pos.x, pos.y + 300, pos.z);
			}
		}

		if (Input::GetButtonTrigger(XINPUT_DOWN) || Input::GetKeyTrigger(VK_S))
		{
			DirectX::XMFLOAT3 pos = GetPos();
			if (pos.y > -300)
			{
				SetPos(pos.x, pos.y - 300, pos.z);
			}
		}
	}
}