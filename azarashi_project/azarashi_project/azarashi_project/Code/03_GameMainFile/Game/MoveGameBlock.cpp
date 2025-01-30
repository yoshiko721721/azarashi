#include "MoveGameBlock.h"
#include "../../08_Collider/BoxCollider.h"

MoveGameBlock::MoveGameBlock(float posX, float posY, float sizeX, float sizeY)
{
    SetPos(posX, posY, 0); 
    SetSize(sizeX, sizeY, 0); 
}

MoveGameBlock::MoveGameBlock(float moveThreshold)
    : moveThreshold(moveThreshold), moveSpeed(5.0f) { // デフォルトの移動速度を設定
}

void MoveGameBlock::Init() {
        Initialize(L"Asset/pic/Box.png");   //背景を初期化
        //SetSize(600.0f, 50.0f, 0.0f);  //大きさを設定
        SetAngle(90.0f);                //角度を設定
        SetColor(1.0f, 1.0f, 1.0f, 1.0f);//角度を設定
    }

void MoveGameBlock::Update() {
    float angle = GetAngle();

    // 傾きが閾値を超えた場合に移動を開始
    if (angle > moveThreshold) {
        SetPos(GetPos().x + moveSpeed, GetPos().y, GetPos().z);
    }
    else if (angle < -moveThreshold) {
        SetPos(GetPos().x - moveSpeed, GetPos().y, GetPos().z);
    }

    // 入力で角度を変える（GameBlockと同様の動作）
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

