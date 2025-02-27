#include "TestWall.h"
#include "../../02_Input/miyoshi_input/ControllerInput.h"
#include "../../03_GameMainFile/Application.h"
#include "../Test/Testfloor.h"

extern float gyroData[3]; // x, y, z軸

float nokosuAngle_Wall; //すみません後で名前ちゃんと考えます


void TestWall::Init()
{
	Initialize(L"asset/pic/Wall.png");   //背景を初期化
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
        SetPos(resetPosX, resetPosY, 0.0f);
        SetAngle(0.0f);
    }


    float angle = GetAngle();
    DirectX::XMFLOAT3 pos = GetPos();

    if (angle < 30.0f && angle > -30.0f)
    {
        float nowAngle = gyroData[1] * 180.0f / M_PI;
        nokosuAngle_Wall = angle + nowAngle * 0.02f;

        if (nokosuAngle_Wall > 30.0f)
        {
            nokosuAngle_Wall = 29.0f;
            return;
        }
        else if (nokosuAngle_Wall < -30.0f)
        {
            nokosuAngle_Wall = -29.0f;
            return;
        }

        //SetAngle(angle);
    }

    // float gyroData[3] = { 0 }; // x, y, z軸
    //if (SDL_GameControllerGetSensorData(Controller::Input::controller, SDL_SENSOR_GYRO, gyroData, 3) == 0)
    // {
#ifdef _DEBUG

    vector<GameBlock*>  gameBlocks = Application::GetInstance()->GetObjects<GameBlock>();
    vector<TestFloor*>  testFloor  = Application::GetInstance()->GetObjects<TestFloor>();

    if (Input::GetKeyPress(VK_LEFT)) {
        SetAngle(GetAngle() + 3.0f);
        //オブジェクトの確認
        bool blockHit = false;
        for (auto block : gameBlocks) {
            if (block != this && blockHit == false) {
                for (auto floor : testFloor) {
                    if (block != floor && !blockHit ) {
                        if (BoxCollider::ColliderWithBox(block, this)) {
                        blockHit = true;
                        CorrectBlockPosition(*this, *block);
                        }
                    }
                }
                
            }
        }
    }
    if (Input::GetKeyPress(VK_RIGHT)) {
        SetAngle(GetAngle() - 3.0f);
        //オブジェクトの確認
        bool blockHit = false;
        for (auto block : gameBlocks) {
            if (block != this && blockHit == false) {
                for (auto floor : testFloor) {
                    if (block != floor && !blockHit) {
                        if (BoxCollider::ColliderWithBox(block, this)) {
                            blockHit = true;
                            CorrectBlockPosition(*this, *block);
                        }
                    }
                }
            }
        }
    }

#endif


    float nowAngle = gyroData[1] * 180.0f / M_PI;

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
    //float angleDegrees = angleRadians * 180.0 / M_PI;

    /*if (angle > 30)
    {
        angle = 30;
    }
    else if (angle < -30)
    {
        angle = -30;
    }*/

    //angle += gyroData[1] * 1.0f;
    SetAngle(nokosuAngle_Wall);
    SetPos(pos.x, pos.y, pos.z);
}


