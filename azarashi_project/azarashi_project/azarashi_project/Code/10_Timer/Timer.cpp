#include "Timer.h"

Timer::Timer() : TimerBg(nullptr), TimerHand(nullptr), angle(0.0f) {
    startTime = std::chrono::high_resolution_clock::now();
}

Timer::~Timer() {
    if (TimerBg) {
        TimerBg->Uninit();
        delete TimerBg;
    }
    if (TimerHand) {
        TimerHand->Uninit();
        delete TimerHand;
    }
}

void Timer::Init() {
    // Œv‚Ì”wŒi‚Ì‰Šú‰»
    TimerBg = new Object;
    TimerBg->Initialize(L"Asset/pic/UI_timer_01.png", 1, 1);
    TimerBg->SetSize(300.0f, 300.0f, 0.0f);

    // Œv‚Ìj‚Ì‰Šú‰»
    TimerHand = new Object;
    TimerHand->Initialize(L"Asset/pic/UI_timer_02.png", 1, 1);
    TimerHand->SetSize(25.0f, 150.0f, 0.0f);
    TimerHand->SetPos(0, -35.0f, 0);
}

void Timer::Update() {
    // Œ»İ‚ğæ“¾‚µA‘OƒtƒŒ[ƒ€‚©‚ç‚ÌŒo‰ßŠÔ‚ğŒvZ
    auto currentTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> deltaTime = currentTime - startTime;
    startTime = currentTime;

    UpdateClockHand(deltaTime.count());
    TimerHand->SetAngle(angle);
}

void Timer::Draw() {
    TimerBg->Draw();
    TimerHand->Draw();
}

void Timer::UpdateClockHand(float deltaTime) {
    // 1•b‚Å360“x‰ñ“]‚·‚é‚Ì‚ÅAj‚Ì‰ñ“]Šp“x‚ğŒvZ
    angle += (360.0f / 60.0f) * -deltaTime;  // 60•b‚Å1ü‚·‚é
}
