#pragma once
#include "../../01_Direct3D/Object.h"
#include "../../02_Input/input.h"
#include "../../02_Input/miyoshi_input/ControllerInput.h"

class TestPointer : public Object
{
public:
    TestPointer() {};
    ~TestPointer() { Uninit(); }
    void Init();  //初期化
    void Update(); //更新 ☆
private:
    int centerX;
    int centerY;
};

