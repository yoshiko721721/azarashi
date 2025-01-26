#include "TestWall.h"
#include "../../02_Input/miyoshi_input/ControllerInput.h"
#define _USE_MATH_DEFINES
#include <math.h>
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
        //GetAngle();
        float angle = GetAngle();
        angle += gyroData[1] * 1.0;
        SetAngle(angle);
       /*float angle; // スケーリング係数を調整 
        angle = GetAngle();
        if (angle >= -30 && angle <= 30)
        {
            angle += gyroData[1] * 1.0f; // スケーリング係数を調整 
        } 

        if (angle > 30)
        {
           angle = 30; // 30度を超える場合は30度に設定
        }
        else if (angle < -30)
        {
           angle = -30; // -30度より小さい場合は-31度に設定
        }

        float radians = angle * M_PI / 180.0; // 角度をラジアンに変換
        DirectX::XMFLOAT3 pos = GetPos();

        DirectX::XMFLOAT2 centerPos = { 0.0f,0.0f };
        // 点を原点に平行移動
        float tempX = pos.x - centerPos.x;
        float tempY = pos.y - centerPos.y;

        float x, y;
        // 点を回転
        x = tempX * cos(radians) - tempY * sin(radians);
        y = tempX * sin(radians) + tempY * cos(radians);

        pos.x = x + centerPos.x;
        pos.y = y + centerPos.y;
        //中心を一旦（100,100）とする
        //angle += gyroData[1] * 1.0f; // スケーリング係数を調整 
        SetAngle(angle);
        SetPos(pos.x, pos.y, pos.z);*/ 

    }
}


