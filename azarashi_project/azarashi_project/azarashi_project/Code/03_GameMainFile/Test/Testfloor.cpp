#include "TestFloor.h"
#include "../../03_GameMainFile/Application.h" 
#include <DirectXMath.h>
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
    SDL_Event& e = Controller::Input::e;
    if (Input::GetButtonTrigger(XINPUT_X))
    {
        float angle = 0; // スケーリング係数を調整 
        SetPos(resetPosX,resetPosY,0);
        SetAngle(angle);
    } 
    
    float gyroData[3] = { 0 }; // x, y, z軸

    if (SDL_PollEvent(&e) != 0)
    {
        if (SDL_GameControllerGetSensorData(Controller::Input::controller, SDL_SENSOR_GYRO, gyroData, 3) == 0)
        {
            float angle = GetAngle();
            DirectX::XMFLOAT3 pos = GetPos();

            //float gyroangle = angle;
            //std::cerr << gyroData[1] << std::endl;
            //std::cout << "お邪魔アイテムを読み込めました" << std::endl;

            angle = gyroData[1] * 0.75f; // スケーリング係数を調整 

            float radians = angle * M_PI / 180.0;
            float cosA = cos(radians);
            float sinA = sin(radians);
            std::cout << "ジャイロ数値: " << gyroData[1] << std::endl;

            //座標を原点にする
            double tempX = pos.x - centerX;
            double tempY = pos.y - centerY;

            //回転させる
            double rotatedX = tempX * cosA - tempY * sinA;
            double rotatedY = tempX * sinA + tempY * cosA;

            //positionに入れる
            pos.x = rotatedX + centerX;
            pos.y = rotatedY + centerY;

            // 角度をラジアンで計算
            float angleRadians = atan2(pos.y - centerY, pos.x - centerX);

            // ラジアンを度数に変換
            float angleDegrees = angleRadians * 180.0 / M_PI;

            if (angleDegrees > 30)
            {
                angleDegrees = 30;
            }
            else if (angleDegrees < -30)
            {
                angleDegrees = - 30;
            }

            //angle += gyroData[1] * 1.0f;
            /*oldgyroData[0] = gyroData[0];
            oldgyroData[1] = gyroData[1];
            oldgyroData[2] = gyroData[2];*/
            SetAngle(angleDegrees);
            SetPos(pos.x, pos.y, pos.z);
            /*float angle = GetAngle();
            angle += gyroData[1] * 1.0f; // スケーリング係数を調整
            if (angle > 30)
            {
                angle = 30;
            }
            else if (angle < -30)
            {
                angle = -30;
            }

            SetAngle(angle);*/
        }
    }
}





