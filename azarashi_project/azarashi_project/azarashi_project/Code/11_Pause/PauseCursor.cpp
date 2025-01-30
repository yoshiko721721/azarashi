#include "PauseCursor.h"
void PauseCursor::Init()
{
	//SetTexture(textures[0]);
	Initialize(L"Asset/pic/PauseCursor.png");   //背景を初期化
	SetPos(-373.0f, 0.0f, 0.0f);      //位置を設定
	SetSize(200.0f, 200.0f, 0.0f);  //大きさを設定
	SetAngle(0.0f);                //角度を設定
	SetColor(1.0f, 1.0f, 1.0f, 1.0f);//角度を設定
}

void PauseCursor::Update(bool pause)//背景のアップデート(いらない気がする)
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