#include "TestWall.h"
#include "../../02_Input/miyoshi_input/ControllerInput.h"
void TestWall::Init()
{
	Initialize(L"asset/pic/block_bronze.png");   //背景を初期化
	//SetPos(100.0f, 64.0f, 0.0f);      //位置を設定
	//SetSize(64.0f, 64.0f, 0.0f);  //大きさを設定
	SetAngle(0.0f);                //角度を設定
	SetColor(1.0f, 1.0f, 1.0f, 0.5f);//角度を設定
}

void TestWall::Update()
{
     SDL_Event& e = Controller::Input::e;
     if (e.type == SDL_CONTROLLERBUTTONDOWN)
     {
        if (e.cbutton.button == SDL_CONTROLLER_BUTTON_X)
        {
            float angle = 0; // スケーリング係数を調整 
            SetAngle(angle);
        }
     }

    float gyroData[3] = {0}; // x, y, z軸
    if (SDL_GameControllerGetSensorData(Controller::Input::controller, SDL_SENSOR_GYRO, gyroData, 3) == 0)
    {
        float angle = GetAngle();
        angle += gyroData[1] * 1.0f; // スケーリング係数を調整 
        SetAngle(angle);
    }
}


