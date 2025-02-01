#include "GameStartUI.h"

//ID3D11ShaderResourceView* LoadTexture(const wchar_t*);

void GameStartUI::Init()
{
	Initialize(L"Asset/pic/Go.png");   //背景を初期化
	SetPos(0.0f, 0.0f, 0.0f);      //位置を設定
	SetSize(1920.0f, 1080.0f, 0.0f);  //大きさを設定
	SetAngle(0.0f);                //角度を設定
	SetColor(1.0f, 1.0f, 1.0f, 1.0f);//角度を設定
}

void GameStartUI::Update()//背景のアップデート(いらない気がする)
{

}
