#include "TestFloor.h"
void TestFloor::Init()
{
	Initialize(L"asset/pic/Box.png");   //背景を初期化
	SetPos(0.0f, 0.0f, 0.0f);      //位置を設定
	SetSize(600.0f, 50.0f, 0.0f);  //大きさを設定
	SetAngle(0.0f);                //角度を設定
	SetColor(1.0f, 1.0f, 1.0f, 1.0f);//角度を設定
}

void TestFloor::Update()
{
    SDL_Event& e = Controller::Input::e;

    if (e.type == SDL_CONTROLLERBUTTONDOWN)
    {
        if (e.cbutton.button == SDL_CONTROLLER_BUTTON_Y)
        {
            float angle = 0; // スケーリング係数を調整 
            SetAngle(angle);
        }
    }

    float gyroData[3] = { 0 }; // x, y, z軸
    if (SDL_GameControllerGetSensorData(Controller::Input::controller, SDL_SENSOR_GYRO, gyroData, 3) == 0)
    {
        float angle = GetAngle();
        angle += gyroData[1] * 1.0f; // スケーリング係数を調整 
        SetAngle(angle);
    }
}

