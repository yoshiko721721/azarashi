#pragma once
#include "../../01_Direct3D/Object.h"
#include "../../02_Input/input.h"

class MoveGameBlock : public Object {
public:
    // �R���X�g���N�^: �X����臒l���w��\
    MoveGameBlock(float moveThreshold);
    ~MoveGameBlock() { Uninit(); }

    // ������
    void Init();

    // �X�V
    void Update();

    float GetFrictionRasistance();
private:
    float moveThreshold; // �X����臒l
    float moveSpeed;     // �ړ����x
    float frictionRasistance;	//���C�W��
};