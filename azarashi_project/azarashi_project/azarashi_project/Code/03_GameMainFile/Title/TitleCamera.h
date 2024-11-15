#pragma once
#include "../../07_Camera/Camera.h"

class TitleCamera :public Camera
{
public:
	void Init();
	void Update();
	void Draw();
	void Uninit();

	//void RightCamera(DirectX::XMFLOAT3 pos);
	///void LeftCamera(DirectX::XMFLOAT3 pos);

private:
	Input input;
};
