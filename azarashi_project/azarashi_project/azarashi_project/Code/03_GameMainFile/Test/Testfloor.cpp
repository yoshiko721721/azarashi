#include "TestFloor.h"
#include "../../03_GameMainFile/Application.h" 
#include <iostream>
#include <DirectXMath.h>

extern float gyroData[3];
float oldgyroData[3] = { 0 }; // x, y, z軸

void TestFloor::Init()
{
    Initialize(L"asset/pic/Floor_11.png");   //背景を初期化
    //SetPos(0.0f, 0.0f, 0.0f);      //位置を設定
    //SetSize(320.0f, 320.0f, 0.0f);  //大きさを設定
    SetAngle(0.0f);                //角度を設定
    SetColor(1.0f, 1.0f, 1.0f, 1.0f);//角度を設定
}

void TestFloor::Update()
{
    /*float angle = 0;
    float Boxangle = 0;
    if (Input::GetButtonTrigger(XINPUT_X))
    {
        Boxangle = -90; // スケーリング係数を調整 
        SetPos(resetPosX, resetPosY, 0);
        SetAngle(Boxangle);
    }

    Boxangle = GetAngle();
    DirectX::XMFLOAT3 pos = GetPos();

    angle = angle + gyroData[1] * 1; // スケーリング係数を調整

    float radians = angle * M_PI / 180.0;
    float cosA = cos(radians);
    float sinA = sin(radians);
    //std::cout << "角度: " << angle << std::endl;

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
    float angleRadians = atan2(centerY - pos.y, centerX - pos.x);

    // ラジアンを度数に変換
    Boxangle = angleRadians * 180.0 / M_PI;

    SetAngle(Boxangle);
    SetPos(pos.x, pos.y, pos.z);*/

    /*angle = angle + gyroData[1] * 1; // スケーリング係数を調整

    float radians = angle * M_PI / 180.0;
    float cosA = cos(radians);
    float sinA = sin(radians);
    std::cout << "角度: " << angle << std::endl;

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
    float angleRadians = atan2(centerY - pos.y,centerX - pos.x);

    // ラジアンを度数に変換
    Boxangle = angleRadians * 180.0 / M_PI;


    SetAngle(Boxangle + 12);
    SetPos(pos.x, pos.y, pos.z);*/
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

            SetAngle(angle);
       // }
    //}*/
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

            SetAngle(angle);
       // }
    //}*/

}


