/*#include "TestPointer.h"
#include "../../02_Input/miyoshi_input/ControllerInput.h"
void TestPointer::Init()
{
    Initialize(L"asset/pic/block_bronze.png");   //�w�i��������
    SetPos(100.0f, 100.0f, 0.0f);      //�ʒu��ݒ�
    SetSize(128.0f, 128.0f, 0.0f);  //�傫����ݒ�
    SetAngle(0.0f);                //�p�x��ݒ�
    SetColor(1.0f, 1.0f, 1.0f, 1.0f);//�p�x��ݒ�
}

void TestPointer::Update()
{
    DirectX::XMFLOAT3 pos = GetPos();

    if (Input::GetKeyPress(VK_LEFT))
    {
        pos.x -= 3;
    }

    if (Input::GetKeyPress(VK_RIGHT))
    {
        pos.x += 3;
    }

    if (Input::GetKeyPress(VK_UP))
	{
        pos.y += 3;
	}

    if (Input::GetKeyPress(VK_DOWN))
	{
        pos.y -= 3;
	}

    SetPos(pos.x,pos.y,pos.z);
}*/
