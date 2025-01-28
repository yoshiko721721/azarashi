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

    float GetFrictionResistance(); // 摩擦抵抗を取得

private:
    float frictionResistance;  // 摩擦抵抗値
    float angle;               // 現在の角度
    bool isFalling;            // 落下中フラグ
    float velocityY;           // 落下速度

    RigidBody rigidBody;       // 物理挙動を管理するRigidBody

    bool CheckCollisionWithGround(); // 地面との衝突判定
    void Destroy();                  // オブジェクトの破壊処理
};
