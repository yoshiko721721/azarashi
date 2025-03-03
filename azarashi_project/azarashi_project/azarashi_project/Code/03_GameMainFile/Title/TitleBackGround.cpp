#include "TitleBackGround.h"
void TitleBackGround::Init()
{
	Initialize(L"Asset/pic/Background_Title.png");   //背景を初期化
	SetPos(0.0f, 0.0f, 0.0f);      //位置を設定
	SetSize(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);  //大きさを設定
	SetAngle(0.0f);                //角度を設定
	SetColor(1.0f, 1.0f, 1.0f, 1.0f);//角度を設定
}

void TitleBackGround::Update(void)
{

	DirectX::XMFLOAT3 pos = GetPos();
	if (Input::GetKeyPress(VK_W))
	{
		pos.x -= 5.0f;
	}
	if (Input::GetKeyTrigger(VK_E))
	{
		pos.x += 5.0f;
	}
	SetPos(pos.x, pos.y, pos.z);
}
