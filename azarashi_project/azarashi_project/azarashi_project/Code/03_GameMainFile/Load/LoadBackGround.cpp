#include "LoadBackGround.h"
#include <cstdlib>
#include <ctime>

void LoadBackGround::Init()
{
	// —”‚ÌƒV[ƒh‚ğİ’è
	std::srand(std::time(0));

	// —”‚ğ¶¬
	int random_number = std::rand() % 5;
	switch (random_number)
	{
	case 0:
		Initialize(L"Asset/pic/Loading01.png");   //”wŒi‚ğ‰Šú‰»
		break;
	case 1:
		Initialize(L"Asset/pic/Loading02.png");   //”wŒi‚ğ‰Šú‰»
		break;
	case 2:
		Initialize(L"Asset/pic/Loading03.png");   //”wŒi‚ğ‰Šú‰»
		break;
	case 3:
		Initialize(L"Asset/pic/Loading04.png");   //”wŒi‚ğ‰Šú‰»
		break;
	case 4:
		Initialize(L"Asset/pic/Loading05.png");   //”wŒi‚ğ‰Šú‰»
		break;
	default:
		break;
	}
	
	SetPos(0.0f, 0.0f, 0.0f);      //ˆÊ’u‚ğİ’è
	SetSize(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);  //‘å‚«‚³‚ğİ’è
	SetAngle(0.0f);                //Šp“x‚ğİ’è
	SetColor(1.0f, 1.0f, 1.0f, 1.0f);//Šp“x‚ğİ’è
}

void LoadBackGround::Update(void)
{
	
}