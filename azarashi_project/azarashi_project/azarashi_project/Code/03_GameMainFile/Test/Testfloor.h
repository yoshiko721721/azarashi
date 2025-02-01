#pragma once
#include "../Game/GameBlock.h"
#include "../../02_Input/input.h"
#include "../../02_Input/miyoshi_input/ControllerInput.h"

class TestFloor:public GameBlock
{
public:
    TestFloor(float startX, float startY, float sizex, float sizey, float setcenterX, float setcenterY/*, float floorcenterX, float floorcenterY*/ )
    {
        DirectX::XMFLOAT3 pos = { startX ,startY ,0.0f };
        DirectX::XMFLOAT3 size = { sizex ,sizey ,0.0f };

        centerX = setcenterX;
        centerY = setcenterY;

        resetPosX = startX;
        resetPosY = startY;

        //floorCenterX = floorcenterX;
        //floorCenterY = floorcenterY;

        SetPos(pos.x, pos.y, pos.z);
        SetSize(size.x, size.y, size.z);
    }
	TestFloor() {};
	~TestFloor() { Uninit(); }
	void Init();  //èâä˙âª
	void Update();//çXêV

private:
    int centerX = 1;
    int centerY = 1;

    float resetPosX;
    float resetPosY;

    float floorCenterX;
    float floorCenterY;
};
