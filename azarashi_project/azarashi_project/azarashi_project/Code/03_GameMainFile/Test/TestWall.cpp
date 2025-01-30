#include "TestWall.h"
#include "../../02_Input/miyoshi_input/ControllerInput.h"

extern float gyroData[3]; // x, y, z軸

void TestWall::Init()
{
	Initialize(L"asset/pic/block_bronze.png");   //背景を初期化
	//SetPos(100.0f, 64.0f, 0.0f);      //位置を設定
	//SetSize(64.0f, 64.0f, 0.0f);  //大きさを設定
	SetAngle(0.0f);                //角度を設定
	SetColor(1.0f, 1.0f, 1.0f, 1.0f);//角度を設定
}

void TestWall::Update()
{
    //SDL_Event& e = Controller::Input::e;
    if (Input::GetButtonTrigger(XINPUT_X))
    {
        SetPos(resetPosX, resetPosY, 0);
        SetAngle(0);
    }

   // float gyroData[3] = { 0 }; // x, y, z軸
    //if (SDL_GameControllerGetSensorData(Controller::Input::controller, SDL_SENSOR_GYRO, gyroData, 3) == 0)
    //{
     float angle = GetAngle();
     DirectX::XMFLOAT3 pos = GetPos();

     //float gyroangle = angle;
     //std::cerr << gyroData[1] << std::endl;
     //std::cout << "お邪魔アイテムを読み込めました" << std::endl;

     angle = gyroData[1] * 0.75f; // スケーリング係数を調整 

     float radians = angle * M_PI / 180.0;
     float cosA = cos(radians);
     float sinA = sin(radians);
     //std::cout << "ラジアン: " << radians << std::endl;

     // Translate point to origin
     double tempX = pos.x - centerX;
     double tempY = pos.y - centerY;

     // Rotate point
     double rotatedX = tempX * cosA - tempY * sinA;
     double rotatedY = tempX * sinA + tempY * cosA;

     // Translate point back
     pos.x = rotatedX + centerX;
     pos.y = rotatedY + centerY;

     // 角度をラジアンで計算
     float angleRadians = atan2(pos.y - resetPosY, pos.x - resetPosX);

     // ラジアンを度数に変換
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


