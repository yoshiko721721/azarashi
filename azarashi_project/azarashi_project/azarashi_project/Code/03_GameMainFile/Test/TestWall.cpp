#include "TestWall.h"
void TestWall::Init()
{
	Initialize(L"asset/block_bronze.png");   //�w�i��������
	SetPos(0.0f, 0.0f, 0.0f);      //�ʒu��ݒ�
	SetSize(200.0f, 200.0f, 0.0f);  //�傫����ݒ�
	SetAngle(0.0f);                //�p�x��ݒ�
	SetColor(1.0f, 1.0f, 1.0f, 1.0f);//�p�x��ݒ�
}

void TestWall::Update(void)
{
    DirectX::XMFLOAT3 pos = GetPos();
    // �v���C���[�̓��͂��`�F�b�N
    if (XINPUT_RIGHT) 
    {
        pos.x += 3;
    }
    else if (XINPUT_LEFT)
    {
        pos.x -= 3;
    }

    SetPos(pos.x,pos.y,pos.z);
}
