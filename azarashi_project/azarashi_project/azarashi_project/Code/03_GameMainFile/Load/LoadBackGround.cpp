#include "LoadBackGround.h"
#include <cstdlib>
#include <ctime>

void LoadBackGround::Init()
{
	// 乱数のシードを設定
	std::srand(std::time(0));

	// 乱数を生成
	int random_number = std::rand() % 5;
	switch (random_number)
	{
	case 0:
		Initialize(L"Asset/pic/Loading01.png");   //背景を初期化
		break;
	case 1:
		Initialize(L"Asset/pic/Loading02.png");   //背景を初期化
		break;
	case 2:
		Initialize(L"Asset/pic/Loading03.png");   //背景を初期化
		break;
	case 3:
		Initialize(L"Asset/pic/Loading04.png");   //背景を初期化
		break;
	case 4:
		Initialize(L"Asset/pic/Loading05.png");   //背景を初期化
		break;
	default:
		break;
	}
	
	SetPos(0.0f, 0.0f, 0.0f);      //位置を設定
	SetSize(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);  //大きさを設定
	SetAngle(0.0f);                //角度を設定
	SetColor(1.0f, 1.0f, 1.0f, 1.0f);//角度を設定
}

void LoadBackGround::Update(void)
{
	
}