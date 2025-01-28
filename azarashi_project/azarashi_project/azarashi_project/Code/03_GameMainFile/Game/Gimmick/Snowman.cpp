#include "Snowman.h"
#include "../../../08_Collider/BoxCollider.h"
#include <iostream>

void Snowman::Init() {
    Initialize(L"Asset/pic/snowman.png");   // �w�i��������
    SetSize(100.0f, 50.0f, 0.0f);          // �傫����ݒ�
    SetColor(1.0f, 1.0f, 1.0f, 1.0f);      // �F��ݒ�
    frictionResistance = 0.5f;              // �������C��R
    angle = 0.0f;                          // �����p�x
    isFalling = false;                     // �����������
    velocityY = 0.0f;                      // �������x
    rigidBody.SetMass(1.0f);                // RigidBody�Ɏ��ʂ�ݒ�
}

void Snowman::Update() {
    // �p�x�̒������s�����͏���
    if (Input::GetKeyPress(VK_LEFT)) {
        SetAngle(GetAngle() + 3);  // ���L�[�������ꂽ��p�x�𑝉�
    }
    else if (Input::GetKeyPress(VK_RIGHT)) {
        SetAngle(GetAngle() - 3);  // �E�L�[�������ꂽ��p�x������
    }
    else if (Input::GetKeyPress(VK_SPACE)) {
        SetAngle(0);  // �X�y�[�X�L�[�������ꂽ��p�x�����Z�b�g
    }

    // �X�m�[�}�����������J�n���邩�ǂ������`�F�b�N
    float currentAngle = GetAngle();
    if (currentAngle < -10.0f && !isFalling) {
        isFalling = true;  // �p�x������臒l����������痎�����J�n
    }

    // �����̕���������RigidBody���g���čX�V
    if (isFalling) {
        // �d�͂�K�p���A�ʒu���X�V
        rigidBody.FreeFall(0.016f);  // 1�t���[��������16ms�����肵�ĕ������Z
        SetPos(GetPos().x, GetPos().y - rigidBody.GetVector().y, GetPos().z);  // ���x�Ɋ�Â��Ĉʒu���X�V

        // �Փ˔���
        if (CheckCollisionWithGround()) {
            Destroy();  // �n�ʂɏՓ˂�����X�m�[�}����j��
        }
    }
}

float Snowman::GetFrictionResistance() {
    return frictionResistance;  // ���C��R�l��Ԃ�
}

bool Snowman::CheckCollisionWithGround() {
    // �P���ȏՓ˔���iBoxCollider���g���ďڍׂȏՓ˔�����\�j
    if (GetPos().y <= 0) {
        return true;  // Y���W��0�ȉ��Ȃ�Փ˂Ƃ݂Ȃ�
    }
    return false;
}

void Snowman::Destroy() {
    // �X�m�[�}���̔j�󏈗�
    Object::Uninit();
}
