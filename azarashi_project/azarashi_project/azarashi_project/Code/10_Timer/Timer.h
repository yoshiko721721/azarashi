#pragma once

#include "..\01_Direct3D\Object.h"
#include <chrono>

class Timer {
public:
    Timer();
    ~Timer();

    void Init();
    void Update();
    void Draw();

private:
    Object* TimerBg;  // ���v�̔w�i
    Object* TimerHand;  // ���v�̐j
    float angle;  // �j�̉�]�p�x
    std::chrono::high_resolution_clock::time_point startTime;  // ��]�J�n����

    void UpdateClockHand(float deltaTime);
};

