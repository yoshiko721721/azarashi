#include "TeamLogo.h"
void TeamLogo::Init()
{
	/*for (int i = 0; i < 4; i++)
	{
		textures[i] = LoadTexture(imgname[i]);
	}*/

	//SetTexture(textures[0]);
	Initialize(L"Asset/pic/TeamLogo.png");   //背景を初期化
	SetPos(0.0f, 0.0f, 0.0f);      //位置を設定
	SetSize(1920.0f, 1080.0f, 0.0f);  //大きさを設定
	SetAngle(0.0f);                //角度を設定
	SetColor(1.0f, 1.0f, 1.0f, 1.0f);//角度を設定
}

void TeamLogo::Update()//背景のアップデート(いらない気がする)
{

}
