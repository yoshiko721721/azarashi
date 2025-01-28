/*#include "TestPointer.h"
#include "../../02_Input/miyoshi_input/ControllerInput.h"
void TestPointer::Init()
{
    Initialize(L"asset/pic/block_bronze.png");   //”wŒi‚ğ‰Šú‰»
    SetPos(100.0f, 100.0f, 0.0f);      //ˆÊ’u‚ğİ’è
    SetSize(128.0f, 128.0f, 0.0f);  //‘å‚«‚³‚ğİ’è
    SetAngle(0.0f);                //Šp“x‚ğİ’è
    SetColor(1.0f, 1.0f, 1.0f, 1.0f);//Šp“x‚ğİ’è
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
