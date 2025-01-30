#include "TestPointer.h"
#include "../../02_Input/miyoshi_input/ControllerInput.h"
void TestPointer::Init()
{
    Initialize(L"asset/pic/タイトルなし.png");   //背景を初期化
    SetPos(0.0f,0.0f, 0.0f);      //位置を設定
    SetSize(0.0f, 0.0f, 0.0f);  //大きさを設定
    SetAngle(0.0f);                //角度を設定
    SetColor(1.0f, 1.0f, 1.0f, 1.0f);//角度を設定
}

void TestPointer::Update()
{
  
}
