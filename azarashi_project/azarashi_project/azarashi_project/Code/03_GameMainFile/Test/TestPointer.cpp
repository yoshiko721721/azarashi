/*#include "TestPointer.h"
#include "../../02_Input/miyoshi_input/ControllerInput.h"
void TestPointer::Init()
{
    Initialize(L"asset/pic/block_bronze.png");   //背景を初期化
    SetPos(100.0f, 100.0f, 0.0f);      //位置を設定
    SetSize(128.0f, 128.0f, 0.0f);  //大きさを設定
    SetAngle(0.0f);                //角度を設定
    SetColor(1.0f, 1.0f, 1.0f, 1.0f);//角度を設定
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
