#include "TestFloor.h"
void TestFloor::Init()
{
	Initialize(L"asset/pic/Box.png");   //�w�i��������
	SetPos(0.0f, 0.0f, 0.0f);      //�ʒu��ݒ�
	SetSize(600.0f, 50.0f, 0.0f);  //�傫����ݒ�
	SetAngle(0.0f);                //�p�x��ݒ�
	SetColor(1.0f, 1.0f, 1.0f, 1.0f);//�p�x��ݒ�
}

void TestFloor::Update()
{
    SDL_Event& e = Controller::Input::e;

    if (e.type == SDL_CONTROLLERBUTTONDOWN)
    {
        if (e.cbutton.button == SDL_CONTROLLER_BUTTON_Y)
        {
            float angle = 0; // �X�P�[�����O�W���𒲐� 
            SetAngle(angle);
        }
    }

    float gyroData[3] = { 0 }; // x, y, z��
    if (SDL_GameControllerGetSensorData(Controller::Input::controller, SDL_SENSOR_GYRO, gyroData, 3) == 0)
    {
        float angle = GetAngle();
        angle += gyroData[1] * 1.0f; // �X�P�[�����O�W���𒲐� 
        SetAngle(angle);
    }
}

