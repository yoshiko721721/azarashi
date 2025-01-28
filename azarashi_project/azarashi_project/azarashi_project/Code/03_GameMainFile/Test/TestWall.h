#pragma once
#include "../Game/GameBlock.h"
#include "../../02_Input/input.h"
#include "../../02_Input/miyoshi_input/ControllerInput.h"

class TestWall : public GameBlock
{
public:
    TestWall(float startX, float startY, float sizex, float sizey,float setcenterX,float setcenterY)
    {
        DirectX::XMFLOAT3 pos = { startX ,startY ,0.0f };
        DirectX::XMFLOAT3 size = { sizex ,sizey ,0.0f };

        centerX = setcenterX;
        centerY = setcenterY;

        SetPos(pos.x, pos.y, pos.z);
        SetSize(size.x, size.y, size.z);
    }
    TestWall() {};
    ~TestWall() { Uninit(); }
    void Init();  //èâä˙âª
    void Update(); //çXêV Åô
private:
    int centerX;
    int centerY;
};
