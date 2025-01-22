#pragma once
#include"../02_Input/input.h"

class Camera
{
public:
    static void Init();
   
    static DirectX::XMMATRIX GetViewMatrix();      //数値を取ってくる

    static void Update();
    static void SetPosition(DirectX::XMVECTOR);
    static void SetTarget(DirectX::XMVECTOR);

protected:
    static DirectX::XMVECTOR m_Position;//cameraの位置用の変数
    static DirectX::XMVECTOR m_Target;
    static DirectX::XMVECTOR m_upDirection;
    static DirectX::XMMATRIX m_viewMatrix;//向きや回転率などを計算し、描画内容を決めたもの
};

