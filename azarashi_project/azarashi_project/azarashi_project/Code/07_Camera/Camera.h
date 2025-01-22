#pragma once
#include"../02_Input/input.h"

class Camera
{
public:
    static void Init();
   
    static DirectX::XMMATRIX GetViewMatrix();      //���l������Ă���

    static void Update();
    static void SetPosition(DirectX::XMVECTOR);
    static void SetTarget(DirectX::XMVECTOR);

protected:
    static DirectX::XMVECTOR m_Position;//camera�̈ʒu�p�̕ϐ�
    static DirectX::XMVECTOR m_Target;
    static DirectX::XMVECTOR m_upDirection;
    static DirectX::XMMATRIX m_viewMatrix;//�������]���Ȃǂ��v�Z���A�`����e�����߂�����
};

