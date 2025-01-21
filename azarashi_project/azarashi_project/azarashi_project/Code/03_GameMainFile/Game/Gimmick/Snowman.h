#pragma once
#include "../../../01_Direct3D/Object.h"
#include "../../../02_Input/Input.h"

class Snowman : public Object {
public:
    Snowman() : frictionRasistance(0.0f), angle(0.0f), isFalling(false), velocityY(0.0f) {}
    ~Snowman() { Uninit(); }
    void Init();  // ������
    void Update();// �X�V

    float GetFrictionRasistance();

private:
    float frictionRasistance;  // ���C�W��
    float angle;               // ���݂̊p�x
    bool isFalling;            // �������t���O
    float velocityY;           // �������x

    bool CheckCollisionWithGround(); // �Փ˔���
    void Destroy();                  // �j�󏈗�
};
