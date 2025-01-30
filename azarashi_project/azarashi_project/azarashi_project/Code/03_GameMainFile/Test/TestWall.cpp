#include "TestWall.h"
#include "../../02_Input/miyoshi_input/ControllerInput.h"
#include <iostream>
#include <DirectXMath.h>

extern float gyroData[3];

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
    /*float angle = 0;
    float Boxangle = 0;

    if (Input::GetButtonTrigger(XINPUT_X) || Input::GetKeyPress(VK_RETURN))
    {
        if (resetPosX < 0)
        {
            Boxangle = 12; // スケーリング係数を調整 
        }
        else if (resetPosX > 0)
        {
            Boxangle = -12;
        }
        SetPos(resetPosX, resetPosY, 0);
        SetAngle(Boxangle);
    }

    if (Input::GetButtonTrigger(XINPUT_LEFT_SHOULDER) || Input::GetKeyPress(VK_LEFT))
    {
        angle = GetAngle();
        Boxangle = GetAngle();
        DirectX::XMFLOAT3 pos = GetPos();

        angle += 0.1; // スケーリング係数を調整

        float radians = angle * M_PI / 180.0;
        float cosA = cos(radians);
        float sinA = sin(radians);

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
        angle = angleRadians * 180.0 / M_PI;

        if (resetPosX < 0)
        {
            if (angle < 32 && angle > 8)
            {
                SetAngle(angle - 12);
            }

        }
        else if (resetPosX > 0)
        {
            if (angle < 8 && angle > -32)
            {
                SetAngle(angle + 12);
            }
        }
        SetPos(pos.x, pos.y, pos.z);
        std::cerr << "角度 " << angle << std::endl;
        std::cerr << "角度 " << angle << std::endl;

        return;
    }


   if (Input::GetButtonTrigger(XINPUT_RIGHT_SHOULDER) || Input::GetKeyPress(VK_RIGHT))
    {
        Boxangle = GetAngle();
        DirectX::XMFLOAT3 pos = GetPos();

        angle -= 0.1; // スケーリング係数を調整

        float radians = angle * M_PI / 180.0;
        float cosA = cos(radians);
        float sinA = sin(radians);

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
        Boxangle = angleRadians * 180.0 / M_PI;

        if (resetPosX < 0)
        {
            if (Boxangle < 32 && Boxangle > 8)
            {
                SetAngle(Boxangle - 12);
            }

        }
        else if (resetPosX > 0)
        {
            if (Boxangle < 8 && Boxangle > -32)
            {
                SetAngle(Boxangle + 12);
            }
        }
        SetPos(pos.x, pos.y, pos.z);
        std::cerr << "角度 " << angle << std::endl;
        return;
    }

    if (Input::GetButtonTrigger(XINPUT_X))
    {
        if (resetPosX < 0)
        {
            Boxangle = 12; // スケーリング係数を調整 
        }
        else if (resetPosX > 0)
        {
            Boxangle = -12;
        }
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

    if (resetPosX < 0)
    {
        if (Boxangle < 32  && Boxangle > 8)
        {
            Boxangle += 12; // スケーリング係数を調整 
        }
    }
    else if (resetPosX > 0)
    {
        if (Boxangle < 8 && Boxangle > -32)
        {
            Boxangle += -12;
        }
    }
    SetPos(resetPosX, resetPosY, 0);
    SetAngle(Boxangle + 12);
    SetPos(pos.x, pos.y, pos.z);*/
      
    //}
    //else if (resetPosX > 0)
    //{
      //  if (Boxangle < -20 && Boxangle > -20)
        //{
          //  SetAngle(Boxangle);
            //SetPos(pos.x, pos.y, pos.z);
        //}
    //}

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
}


