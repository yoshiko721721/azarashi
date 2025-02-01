#include "TestWall.h"
#include "../../02_Input/miyoshi_input/ControllerInput.h"
#include "../../03_GameMainFile/Application.h"

extern float gyroData[3]; // x, y, z��

float nokosuAngle_Wall; //���݂܂����Ŗ��O�����ƍl���܂�


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


    float angle = GetAngle();
    DirectX::XMFLOAT3 pos = GetPos();

    if (angle < 30 && angle > -30)
    {
        float nowAngle = gyroData[1] * 180.0 / M_PI;
        nokosuAngle_Wall = angle + nowAngle * 0.02f;

        if (nokosuAngle_Wall > 30)
        {
            nokosuAngle_Wall = 29;
            return;
        }
        else if (nokosuAngle_Wall < -30)
        {
            nokosuAngle_Wall = -29;
            return;
        }

        //SetAngle(angle);
    }

    // float gyroData[3] = { 0 }; // x, y, z��
    //if (SDL_GameControllerGetSensorData(Controller::Input::controller, SDL_SENSOR_GYRO, gyroData, 3) == 0)
    // {
#ifdef _DEBUG

    vector<GameBlock*>	 gameBlocks = Application::GetInstance()->GetObjects<GameBlock>();


    if (Input::GetKeyPress(VK_LEFT)) {
        SetAngle(GetAngle() + 3);
        //�I�u�W�F�N�g�̊m�F
        bool blockHit = false;
        for (auto block : gameBlocks) {
            if (block != this && blockHit == false) {
                if (BoxCollider::ColliderWithBox(block, this)) {
                    blockHit = true;
                    CorrectBlockPosition(*this, *block);
                }
            }
        }
    }
    if (Input::GetKeyPress(VK_RIGHT)) {
        SetAngle(GetAngle() - 3);
        //�I�u�W�F�N�g�̊m�F
        bool blockHit = false;
        for (auto block : gameBlocks) {
            if (block != this && blockHit == false) {
                if (BoxCollider::ColliderWithBox(block, this)) {
                    blockHit = true;
                    CorrectBlockPosition(*this, *block);
                }
            }
        }
    }

#endif


    float nowAngle = gyroData[1] * 180.0 / M_PI;

    nowAngle = nowAngle * 0.02f; // �X�P�[�����O�W���𒲐� 

    float radians = nowAngle * M_PI / 180.0;
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
    //float angleRadians = atan2(pos.y + resetPosY, pos.x + resetPosX);

    // ���W�A����x���ɕϊ�
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


