#include "TestFloor.h"
#include "../../03_GameMainFile/Application.h" 
void TestFloor::Init()
{
	Initialize(L"asset/pic/Box.png");   //�w�i��������
	//SetPos(0.0f, 0.0f, 0.0f);      //�ʒu��ݒ�
	//SetSize(320.0f, 64.0f, 0.0f);  //�傫����ݒ�
	SetAngle(0.0f);                //�p�x��ݒ�
	SetColor(1.0f, 1.0f, 1.0f, 1.0f);//�p�x��ݒ�

	/*if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK | SDL_INIT_GAMECONTROLLER) < 0)
	{
		//std::cerr << "SDL�̏������Ɏ��s���܂����BSDL_Error: " << SDL_GetError() << std::endl;
		return;
	}

	InitializeController();

	// �W���C���Z���T�[��L����
	SDL_GameControllerSetSensorEnabled(controller, SDL_SENSOR_GYRO, SDL_TRUE);*/
}

void TestFloor::Update()
{
    SDL_Event& e = Controller::Input::e;

    if (e.type == SDL_CONTROLLERBUTTONDOWN)
    {
        if (e.cbutton.button == SDL_CONTROLLER_BUTTON_Y)
        {
            float angle = 90; // �X�P�[�����O�W���𒲐� 
            SetAngle(angle);
        }
    }

    /*float gyroData[3] = {0}; // x, y, z��
    if (SDL_GameControllerGetSensorData(Controller::Input::controller, SDL_SENSOR_GYRO, gyroData, 3) == 0)
    {
        float angle = GetAngle();
        angle += gyroData[1] * 1.0f; // �X�P�[�����O�W���𒲐� 
        SetAngle(angle);
    }*/
}





