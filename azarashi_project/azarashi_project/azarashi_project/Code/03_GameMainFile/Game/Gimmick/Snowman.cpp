#include "Snowman.h"
#include "../../../08_Collider/BoxCollider.h"

void Snowman::Init()
{
    Initialize(L"Asset/pic/snowman.png");   // �w�i��������
    SetSize(100.0f, 50.0f, 0.0f);          // �傫����ݒ�
    SetColor(1.0f, 1.0f, 1.0f, 1.0f);      // �F��ݒ�
    frictionRasistance = 0.5f;             // ���C�W���̏����l
    angle = 0.0f;                          // �����p�x
    isFalling = false;                     // ������Ԃ̏����l
    velocityY = 0.0f;                      // �������x
}

void Snowman::Update(void)
{
    // ���͂ɂ��p�x�ύX
    if (Input::GetKeyPress(VK_LEFT)) {
        SetAngle(GetAngle() + 3);
    }
    else if (Input::GetKeyPress(VK_RIGHT)) {
        SetAngle(GetAngle() - 3);
    }
    else if (Input::GetKeyPress(VK_SPACE)) {
        SetAngle(0);
    }

    // �X������
    float currentAngle = GetAngle();
    if (currentAngle < -10.0f && !isFalling) {
        isFalling = true; // �����n�߂�
    }

    // ��������
    if (isFalling) {
        if (GetPos().y < 0) {
            velocityY += 9.8f * 0.016f; // �d�͉����x (����16ms/frame)
            SetPos(GetPos().x, GetPos().y - velocityY, GetPos().z);
        }
        else {
            SetPos(GetPos().x, 0.0f, GetPos().z);
        }
        // �Փˌ��m
        if (CheckCollisionWithGround()) {
            Destroy(); // �j�󏈗�
        }
    }
}

float Snowman::GetFrictionRasistance()
{
    return frictionRasistance;
}

bool Snowman::CheckCollisionWithGround()
{

}


void Snowman::Destroy()
{
    // �I�u�W�F�N�g�̔j�󏈗�
}
