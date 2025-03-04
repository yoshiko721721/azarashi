#include "TestFloor.h"
#include "../../03_GameMainFile/Application.h" 
#include <DirectXMath.h>

extern float gyroData[3]; // x, y, z軸

float nokosuAngle_Floor; //すみません後で名前ちゃんと考えます

void TestFloor::Init()
{
	Initialize(L"asset/pic/Box.png");   //背景を初期化
	//SetPos(0.0f, 0.0f, 0.0f);      //位置を設定
	//SetSize(320.0f, 64.0f, 0.0f);  //大きさを設定
	SetAngle(0.0f);                //角度を設定
	SetColor(1.0f, 1.0f, 1.0f, 1.0f);//角度を設定

	/*if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK | SDL_INIT_GAMECONTROLLER) < 0)
	{
		//std::cerr << "SDLの初期化に失敗しました。SDL_Error: " << SDL_GetError() << std::endl;
		return;
	}

	InitializeController();

	// ジャイロセンサーを有効化
	SDL_GameControllerSetSensorEnabled(controller, SDL_SENSOR_GYRO, SDL_TRUE);*/
}

void TestFloor::Update()
{
    //SDL_Event& e = Controller::Input::e;
    if (Input::GetButtonTrigger(XINPUT_X))
    {
        SetPos(resetPosX, resetPosY, 0.0f);
        SetAngle(0.0f);
    }
    

    float angle = GetAngle();
    DirectX::XMFLOAT3 pos = GetPos();

    if (angle < 30.0f && angle > -30.0f)
    {
        float nowAngle = gyroData[1] * 180.0f / M_PI;
        unificationFloorAngle = angle + nowAngle * 0.02f;

        if (unificationFloorAngle > 30.0f)
        {
            unificationFloorAngle = 29.0f;
            return;
        }
        else if (unificationFloorAngle < -30.0f)
        {
            unificationFloorAngle = -29.0f;
            return;
        }

        //SetAngle(angle);
    }

   // float gyroData[3] = { 0 }; // x, y, z軸
   //if (SDL_GameControllerGetSensorData(Controller::Input::controller, SDL_SENSOR_GYRO, gyroData, 3) == 0)
   // {

        nowAngle = gyroData[1] * 180.0f / M_PI;

        nowAngle = nowAngle * 0.02f; // スケーリング係数を調整 

        float radians = nowAngle * M_PI / 180.0f;
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
        //float angleRadians = atan2(pos.y + resetPosY, pos.x + resetPosX);

        // ラジアンを度数に変換
        //float angleDegrees = angleRadians * 180.0f / M_PI;

        /*if (angle > 30)
        {
            angle = 30;
        }
        else if (angle < -30)
        {
            angle = -30;
        }*/

        //angle += gyroData[1] * 1.0f;
        SetAngle(unificationFloorAngle);
        SetPos(pos.x, pos.y, pos.z);
   // }
}





