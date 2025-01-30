#include "TestWall.h"
#include "../../02_Input/miyoshi_input/ControllerInput.h"

extern float gyroData[3]; // x, y, z��

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
    //SDL_Event& e = Controller::Input::e;
    if (Input::GetButtonTrigger(XINPUT_X))
    {
        SetPos(resetPosX, resetPosY, 0);
        SetAngle(0);
    }

   // float gyroData[3] = { 0 }; // x, y, z��
    //if (SDL_GameControllerGetSensorData(Controller::Input::controller, SDL_SENSOR_GYRO, gyroData, 3) == 0)
    //{
     float angle = GetAngle();
     DirectX::XMFLOAT3 pos = GetPos();

     //float gyroangle = angle;
     //std::cerr << gyroData[1] << std::endl;
     //std::cout << "���ז��A�C�e����ǂݍ��߂܂���" << std::endl;

     angle = gyroData[1] * 0.75f; // �X�P�[�����O�W���𒲐� 

     float radians = angle * M_PI / 180.0;
     float cosA = cos(radians);
     float sinA = sin(radians);
     //std::cout << "���W�A��: " << radians << std::endl;

     // Translate point to origin
     double tempX = pos.x - centerX;
     double tempY = pos.y - centerY;

     // Rotate point
     double rotatedX = tempX * cosA - tempY * sinA;
     double rotatedY = tempX * sinA + tempY * cosA;

     // Translate point back
     pos.x = rotatedX + centerX;
     pos.y = rotatedY + centerY;

     // �p�x�����W�A���Ōv�Z
     float angleRadians = atan2(pos.y - resetPosY, pos.x - resetPosX);

     // ���W�A����x���ɕϊ�
     float angleDegrees = angleRadians * 180.0 / M_PI;

     if (angle > 30)
     {
         angle = 30;
     }
     else if (angle < -30)
     {
         angle = -30;
     }

     //angle += gyroData[1] * 1.0f;
     if (resetPosX > 0)
     {

         SetAngle(angleDegrees + 80);

     }
     else if (resetPosX < 0)
     {

         SetAngle(angleDegrees - 80);

     }

     SetPos(pos.x, pos.y, pos.z);
   // }
}


