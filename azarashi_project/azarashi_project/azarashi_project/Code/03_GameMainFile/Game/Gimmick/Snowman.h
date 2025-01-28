#pragma once
#include "../../../01_Direct3D/Object.h"
#include "../../../02_Input/Input.h"
#include "../../RigidBody.h"

class Snowman : public Object {
public:
    Snowman();
    ~Snowman();

    void Init();   
    void Update(); 

    float GetFrictionResistance(); // ���C��R���擾

private:
    float frictionResistance;  // ���C��R�l
    float angle;               // ���݂̊p�x
    bool isFalling;            // �������t���O
    float velocityY;           // �������x

    RigidBody rigidBody;       // �����������Ǘ�����RigidBody

    bool CheckCollisionWithGround(); // �n�ʂƂ̏Փ˔���
    void Destroy();                  // �I�u�W�F�N�g�̔j�󏈗�
};
