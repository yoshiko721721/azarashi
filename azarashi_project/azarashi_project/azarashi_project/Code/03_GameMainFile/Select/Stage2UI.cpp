#include "Stage2UI.h"
void Stage2UI::Init()
{
	/*for (int i = 0; i < 4; i++)
	{
		textures[i] = LoadTexture(imgname[i]);
	}*/

	//SetTexture(textures[0]);
	Initialize(imgname[0]);   //背景を初期化
	SetPos(-200.0f, -170.0f, 0.0f);      //位置を設定
	SetSize(500.0f, 500.0f, 0.0f);  //大きさを設定
	SetAngle(0.0f);                //角度を設定
	SetColor(1.0f, 1.0f, 1.0f, 1.0f);//角度を設定
}

void Stage2UI::Update(int selectPage)//背景のアップデート(いらない気がする)
{
	SetTexture(imgname[selectPage]);
}
