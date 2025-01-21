#pragma once
#include "../../../01_Direct3D/Object.h"
#include "../../../02_Input/Input.h"

class Snowman : public Object {
public:
    Snowman() : frictionRasistance(0.0f), angle(0.0f), isFalling(false), velocityY(0.0f) {}
    ~Snowman() { Uninit(); }
    void Init();  // 初期化
    void Update();// 更新

    float GetFrictionRasistance();

private:
    float frictionRasistance;  // 摩擦係数
    float angle;               // 現在の角度
    bool isFalling;            // 落下中フラグ
    float velocityY;           // 落下速度

    bool CheckCollisionWithGround(); // 衝突判定
    void Destroy();                  // 破壊処理
};
