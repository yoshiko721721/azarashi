#pragma once
#include "../../03_GameMainFile/Game/GameBlock.h"
#include "../../02_Input/input.h"

class MoveGameBlock : public GameBlock {
public:
    // コンストラクタ: 傾きの閾値を指定可能
    MoveGameBlock(float posX, float posY, float sizeX, float sizeY) : GameBlock(posX, posY, sizeX, sizeY) {};
    MoveGameBlock(float moveThreshold);
    ~MoveGameBlock() { Uninit(); }

    // 初期化
    void Init();

    // 更新
    void Update();

    float GetFrictionRasistance();
private:
    float moveThreshold; // 傾きの閾値
    float moveSpeed;     // 移動速度
    float frictionRasistance;	//摩擦係数
};