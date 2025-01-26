#include "TestWall.h"
#include "../../02_Input/miyoshi_input/ControllerInput.h"
#define _USE_MATH_DEFINES
#include <math.h>
void TestWall::Init()
{
	Initialize(L"asset/pic/block_bronze.png");   //�w�i��������
	//SetPos(100.0f, 64.0f, 0.0f);      //�ʒu��ݒ�
	//SetSize(64.0f, 64.0f, 0.0f);  //�傫����ݒ�
	SetAngle(0.0f);                //�p�x��ݒ�
	SetColor(1.0f, 1.0f, 1.0f, 1.0f);//�p�x��ݒ�
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
        //GetAngle();
        float angle = GetAngle();
        angle += gyroData[1] * 1.0;
        SetAngle(angle);
       /*float angle; // �X�P�[�����O�W���𒲐� 
        angle = GetAngle();
        if (angle >= -30 && angle <= 30)
        {
            angle += gyroData[1] * 1.0f; // �X�P�[�����O�W���𒲐� 
        } 

        if (angle > 30)
        {
           angle = 30; // 30�x�𒴂���ꍇ��30�x�ɐݒ�
        }
        else if (angle < -30)
        {
           angle = -30; // -30�x��菬�����ꍇ��-31�x�ɐݒ�
        }

        float radians = angle * M_PI / 180.0; // �p�x�����W�A���ɕϊ�
        DirectX::XMFLOAT3 pos = GetPos();

        DirectX::XMFLOAT2 centerPos = { 0.0f,0.0f };
        // �_�����_�ɕ��s�ړ�
        float tempX = pos.x - centerPos.x;
        float tempY = pos.y - centerPos.y;

        float x, y;
        // �_����]
        x = tempX * cos(radians) - tempY * sin(radians);
        y = tempX * sin(radians) + tempY * cos(radians);

        pos.x = x + centerPos.x;
        pos.y = y + centerPos.y;
        //���S����U�i100,100�j�Ƃ���
        //angle += gyroData[1] * 1.0f; // �X�P�[�����O�W���𒲐� 
        SetAngle(angle);
        SetPos(pos.x, pos.y, pos.z);*/ 

    }
}


