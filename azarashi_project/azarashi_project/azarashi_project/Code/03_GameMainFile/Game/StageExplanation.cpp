#include "StageExplanation.h"
void StageExplanation::Init()
{
	/*for (int i = 0; i < 4; i++)
	{
		textures[i] = LoadTexture(imgname[i]);
	}*/

	//SetTexture(textures[0])   //背景を初期化
	Initialize(L"Asset/pic/Controller.png");
	SetPos(0.0f, 0.0f, 0.0f);      //位置を設定
	SetSize(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);  //大きさを設定
	SetAngle(0.0f);                //角度を設定
	SetColor(1.0f, 1.0f, 1.0f, 1.0f);//角度を設定
}

void StageExplanation::Update()//背景のアップデート(いらない気がする)
{

}
