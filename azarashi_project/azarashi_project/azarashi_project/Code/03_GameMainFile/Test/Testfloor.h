#pragma once
#include "../../01_Direct3D/Object.h"
#include "../../02_Input/input.h"

class TestFloor:public Object
{
public:
	TestFloor(float startX, float startY, float sizex, float sizey)
	{
		DirectX::XMFLOAT3 pos = { startX ,startY ,0.0f };
		DirectX::XMFLOAT3 size = { sizex ,sizey ,0.0f };

		SetPos(pos.x, pos.y, pos.z);
		SetSize(size.x, size.y, size.z);
	}
	TestFloor() {};
	~TestFloor() { Uninit(); }
	void Init();  //èâä˙âª
	void Update();//çXêV
private:
	//Input input;
};
