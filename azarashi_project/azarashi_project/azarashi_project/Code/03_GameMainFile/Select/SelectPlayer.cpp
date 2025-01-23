#include "SelectPlayer.h"
void SelectPlayer::Init()
{
	Initialize(L"Asset/pic/Player_Idle.png");   //背景を初期化
	SetPos(-620.0f, 0.0f, 0.0f);      //位置を設定
	SetSize(360.0f, 195.0f, 0.0f);  //大きさを設定
	SetAngle(0.0f);                //角度を設定
	SetColor(1.0f, 1.0f, 1.0f, 1.0f);//角度を設定
}

void SelectPlayer::Update(int selectStage)//背景のアップデート(いらない気がする)
{
	XMFLOAT3 pos = GetPos();


	switch (selectStage)
	{
	case 0:
	{
		pos.x = -620;
		pos.y =   30;
		break;
	}
	case 1:
	{
		pos.x = -240;
		pos.y = -190;
		break;
	}
	case 2:
	{
		pos.x =  240;
		pos.y =   30;
		break;
	}
	case 3:
	{
		pos.x =  620;
		pos.y = -190;
		break;
	}
	default:
		break;
	}


	SetPos(pos.x, pos.y, pos.z);
}