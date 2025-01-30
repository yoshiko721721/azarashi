#pragma once
#include "../GameBlock.h"
#include "../../../02_Input/input.h"
#include "../../../02_Input/miyoshi_input/ControllerInput.h"

class GameBlock_stop : public GameBlock
{
public:
    GameBlock_stop(float startX, float startY, float sizex, float sizey)
    {
        DirectX::XMFLOAT3 pos = { startX ,startY ,0.0f };
        DirectX::XMFLOAT3 size = { sizex ,sizey ,0.0f };

        resetPosX = startX;
        resetPosY = startY;

        SetPos(pos.x, pos.y, pos.z);
        SetSize(size.x, size.y, size.z);
    }
    GameBlock_stop() {};
    ~GameBlock_stop() { Uninit(); }
    void Init();  //èâä˙âª
    void Update(); //çXêV Åô
private:
    int centerX = 1;
    int centerY = 1;

    float resetPosX;
    float resetPosY;
};