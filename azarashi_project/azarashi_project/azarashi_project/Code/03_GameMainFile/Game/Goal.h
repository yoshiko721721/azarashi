#pragma once
#include "../../01_Direct3D/Object.h"
#include "../../02_Input/input.h"
#include "../../02_Input/miyoshi_input/ControllerInput.h"

class Goal : public Object
{
public:
    Goal(float startX, float startY, float sizex, float sizey)
    {
        /*DirectX::XMFLOAT3 pos = {startX ,startY ,0.0f};
        DirectX::XMFLOAT3 size = { sizex ,sizey ,0.0f };
        Posx
        SetPos(pos.x, pos.y, pos.z);
        SetSize(size.x, size.y, size.z);*/
        Posx = startX;
        Posy = startY;

    }
    Goal() {};
    ~Goal() { Uninit(); }
    void Init();  //èâä˙âª
    void Update(); //çXêV Åô
    bool GetGoal() { return isGoalAchieved; };
private:
    bool isGoalAchieved = false;

    float Posx;
    float Posy;
};
