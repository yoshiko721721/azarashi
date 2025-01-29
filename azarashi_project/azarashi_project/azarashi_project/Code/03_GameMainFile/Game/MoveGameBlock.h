#pragma once
#include "../../03_GameMainFile/Game/GameBlock.h"
#include "../../02_Input/input.h"

class MoveGameBlock : public GameBlock {
public:
    // �R���X�g���N�^: �X����臒l���w��\
    MoveGameBlock(float posX, float posY, float sizeX, float sizeY);
    MoveGameBlock(float moveThreshold);
    ~MoveGameBlock() { Uninit(); }

    // ������
    void Init();

    // �X�V
    void Update();

private:
    float moveThreshold; // �X����臒l
    float moveSpeed;     // �ړ����x

};