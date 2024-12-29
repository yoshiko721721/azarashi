#pragma once

#include <chrono>
#include <thread>
#include"../02_Input/input.h"


using namespace std;

class Pause {
private:
    int key;

public:
    void apply();
    void maladaptive();
    bool isPaused() const;

    bool paused = false;
};