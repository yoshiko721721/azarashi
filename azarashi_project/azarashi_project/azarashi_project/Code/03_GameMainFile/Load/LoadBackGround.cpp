#include "LoadBackGround.h"
#include <cstdlib>
#include <ctime>

void LoadBackGround::Init()
{
	// �����̃V�[�h��ݒ�
	std::srand(std::time(0));

	// �����𐶐�
	int random_number = std::rand() % 5;
	switch (random_number)
	{
	case 0:
		Initialize(L"Asset/pic/Loading01.png");   //�w�i��������
		break;
	case 1:
		Initialize(L"Asset/pic/Loading02.png");   //�w�i��������
		break;
	case 2:
		Initialize(L"Asset/pic/Loading03.png");   //�w�i��������
		break;
	case 3:
		Initialize(L"Asset/pic/Loading04.png");   //�w�i��������
		break;
	case 4:
		Initialize(L"Asset/pic/Loading05.png");   //�w�i��������
		break;
	default:
		break;
	}
	
	SetPos(0.0f, 0.0f, 0.0f);      //�ʒu��ݒ�
	SetSize(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);  //�傫����ݒ�
	SetAngle(0.0f);                //�p�x��ݒ�
	SetColor(1.0f, 1.0f, 1.0f, 1.0f);//�p�x��ݒ�
}

void LoadBackGround::Update(void)
{
	
}