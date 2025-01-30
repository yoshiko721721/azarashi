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

        resetPosX = startX;
        resetPosY = startY;

        SetPos(pos.x, pos.y, pos.z);
        SetSize(size.x, size.y, size.z);
    }
    TestWall() {};
    ~TestWall() { Uninit(); }
    void Init();  //������
    void Update(); //�X�V ��
private:
    int centerX = 1;
    int centerY = 1;

    float resetPosX;
    float resetPosY;
};
