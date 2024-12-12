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
    Object* TimerBg;  // Œv‚Ì”wŒi
    Object* TimerHand;  // Œv‚Ìj
    float angle;  // j‚Ì‰ñ“]Šp“x
    std::chrono::high_resolution_clock::time_point startTime;  // ‰ñ“]ŠJn

    void UpdateClockHand(float deltaTime);
};

