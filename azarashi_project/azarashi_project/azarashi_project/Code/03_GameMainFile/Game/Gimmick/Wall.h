#pragma once
#include "../GameBlock.h"
#include "../../../02_Input/input.h"
#include "../../../02_Input/miyoshi_input/ControllerInput.h"

class Wall : public GameBlock
{
public:
    Wall(float startX, float startY, float sizex, float sizey)
    {
        DirectX::XMFLOAT3 pos = { startX ,startY ,0.0f };
        DirectX::XMFLOAT3 size = { sizex ,sizey ,0.0f };

        SetPos(pos.x, pos.y, pos.z);
        SetSize(size.x, size.y, size.z);
    }
    Wall() {};
    ~Wall() { Uninit(); }
    void Init();  //èâä˙âª
    void Update(); //çXêV Åô
};
