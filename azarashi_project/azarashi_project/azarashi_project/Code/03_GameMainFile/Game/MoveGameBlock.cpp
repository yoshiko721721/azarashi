#include "MoveGameBlock.h"
#include "../../08_Collider/BoxCollider.h"

MoveGameBlock::MoveGameBlock(float posX, float posY, float sizeX, float sizeY)
{
    SetPos(posX, posY, 0); 
    SetSize(sizeX, sizeY, 0); 
}

MoveGameBlock::MoveGameBlock(float moveThreshold)
    : moveThreshold(moveThreshold), moveSpeed(5.0f) { // �f�t�H���g�̈ړ����x��ݒ�
}

void MoveGameBlock::Init() {
        Initialize(L"Asset/pic/Box.png");   //�w�i��������
        //SetSize(600.0f, 50.0f, 0.0f);  //�傫����ݒ�
        SetAngle(90.0f);                //�p�x��ݒ�
        SetColor(1.0f, 1.0f, 1.0f, 1.0f);//�p�x��ݒ�
    }

void MoveGameBlock::Update() {
    float angle = GetAngle();

    // �X����臒l�𒴂����ꍇ�Ɉړ����J�n
    if (angle > moveThreshold) {
        SetPos(GetPos().x + moveSpeed, GetPos().y, GetPos().z);
    }
    else if (angle < -moveThreshold) {
        SetPos(GetPos().x - moveSpeed, GetPos().y, GetPos().z);
    }

    // ���͂Ŋp�x��ς���iGameBlock�Ɠ��l�̓���j
    if (Input::GetKeyPress(VK_LEFT)) {
        SetAngle(GetAngle() + 3);
    }
    else if (Input::GetKeyPress(VK_RIGHT)) {
        SetAngle(GetAngle() - 3);
    }
    else if (Input::GetKeyPress(VK_SPACE)) {
        SetAngle(0);
    }

    GameBlock::Update();
}

