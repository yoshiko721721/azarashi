#include "TestWall.h"
#include "../../02_Input/miyoshi_input/ControllerInput.h"
void TestWall::Init()
{
	Initialize(L"asset/pic/block_bronze.png");   //�w�i��������
	//SetPos(100.0f, 64.0f, 0.0f);      //�ʒu��ݒ�
	//SetSize(64.0f, 64.0f, 0.0f);  //�傫����ݒ�
	SetAngle(0.0f);                //�p�x��ݒ�
	SetColor(1.0f, 1.0f, 1.0f, 0.5f);//�p�x��ݒ�
}

void TestWall::Update()
{
     SDL_Event& e = Controller::Input::e;
     if (e.type == SDL_CONTROLLERBUTTONDOWN)
     {
        if (e.cbutton.button == SDL_CONTROLLER_BUTTON_X)
        {
            float angle = 0; // �X�P�[�����O�W���𒲐� 
            SetAngle(angle);
        }
     }

    float gyroData[3] = {0}; // x, y, z��
    if (SDL_GameControllerGetSensorData(Controller::Input::controller, SDL_SENSOR_GYRO, gyroData, 3) == 0)
    {
        float angle = GetAngle();
        angle += gyroData[1] * 1.0f; // �X�P�[�����O�W���𒲐� 
        SetAngle(angle);
    }
}


