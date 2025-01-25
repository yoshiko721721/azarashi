#pragma once
#include"../02_Input/input.h"
#include "../03_GameMainFile/Game/GamePointer.h"
#include "../12_CSVMapLoader/CSVMapLoader.h"
#include "../03_GameMainFile/Application.h"
#include "../03_GameMainFile/Test/TestScene_You.h"

class Camera
{
private:
    static Object* lockObj ;

public:
    Camera ();
    static void Init ( );


    static DirectX::XMMATRIX GetViewMatrix ( );      //���l������Ă���

    static void Update ( );
    static void SetPosition ( DirectX::XMVECTOR );
    static void SetTarget ( DirectX::XMVECTOR );

    static void Lock ( Object* obj );
    static void Unlock ( );


protected:
    static DirectX::XMVECTOR m_Position;//camera�̈ʒu�p�̕ϐ�
    static DirectX::XMVECTOR m_Target;
    static DirectX::XMVECTOR m_upDirection;
    static DirectX::XMMATRIX m_viewMatrix;//�������]���Ȃǂ��v�Z���A�`����e�����߂�����
};

