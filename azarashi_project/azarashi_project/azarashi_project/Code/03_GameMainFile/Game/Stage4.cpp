#include "Stage4.h"

//ID3D11ShaderResourceView* LoadTexture(const wchar_t*);

void Stage4::Init()
{
	//SetTexture(textures[0]);
	Initialize(L"Asset/pic/SelectUI/Stageselect_1_4.png");   //背景を初期化
	SetPos(580.0f, -170.0f, 0.0f);      //位置を設定
	SetSize(500.0f, 500.0f, 0.0f);  //大きさを設定
	SetAngle(0.0f);                //角度を設定
	SetColor(1.0f, 1.0f, 1.0f, 1.0f);//角度を設定
}

void Stage4::Update(int selectPage)//背景のアップデート(いらない気がする)
{
	//SetTexture(imgname[selectPage]);
}
