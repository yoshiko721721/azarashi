#include "TestWall.h"
#include "../../02_Input/miyoshi_input/ControllerInput.h"
void TestWall::Init()
{
	Initialize(L"asset/pic/block_bronze.png");   //”wŒi‚ð‰Šú‰»
	//SetPos(100.0f, 64.0f, 0.0f);      //ˆÊ’u‚ðÝ’è
	//SetSize(64.0f, 64.0f, 0.0f);  //‘å‚«‚³‚ðÝ’è
	SetAngle(0.0f);                //Šp“x‚ðÝ’è
	SetColor(1.0f, 1.0f, 1.0f, 0.5f);//Šp“x‚ðÝ’è
}

void TestWall::Update()
{
    
    if (Input::GetButtonTrigger(XINPUT_X))
    {
        float angle = 0; // ƒXƒP[ƒŠƒ“ƒOŒW”‚ð’²® 
        SetAngle(angle);
    }

    float gyroData[3] = {0}; // x, y, zŽ²
    if (SDL_GameControllerGetSensorData(Controller::Input::controller, SDL_SENSOR_GYRO, gyroData, 3) == 0)
    {
        float angle = GetAngle();
        angle += gyroData[1] * 1.0f; // ƒXƒP[ƒŠƒ“ƒOŒW”‚ð’²® 
        if (angle > 30)
        {
            angle = 30;
        }
        else if (angle < -30)
        {
            angle = -30;
        }

        SetAngle(angle);
    }
}


