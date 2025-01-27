#include "Snowman.h"
#include "../../../08_Collider/BoxCollider.h"

void Snowman::Init()
{
    Initialize(L"Asset/pic/snowman.png");   // 背景を初期化
    SetSize(100.0f, 50.0f, 0.0f);          // 大きさを設定
    SetColor(1.0f, 1.0f, 1.0f, 1.0f);      // 色を設定
    frictionRasistance = 0.5f;             // 摩擦係数の初期値
    angle = 0.0f;                          // 初期角度
    isFalling = false;                     // 落下状態の初期値
    velocityY = 0.0f;                      // 初期速度
}

void Snowman::Update(void)
{
    // 入力による角度変更
    if (Input::GetKeyPress(VK_LEFT)) {
        SetAngle(GetAngle() + 3);
    }
    else if (Input::GetKeyPress(VK_RIGHT)) {
        SetAngle(GetAngle() - 3);
    }
    else if (Input::GetKeyPress(VK_SPACE)) {
        SetAngle(0);
    }

    // 傾き判定
    float currentAngle = GetAngle();
    if (currentAngle < -10.0f && !isFalling) {
        isFalling = true; // 動き始める
    }

    // 落下処理
    if (isFalling) {
        if (GetPos().y < 0) {
            velocityY += 9.8f * 0.016f; // 重力加速度 (仮に16ms/frame)
            SetPos(GetPos().x, GetPos().y - velocityY, GetPos().z);
        }
        else {
            SetPos(GetPos().x, 0.0f, GetPos().z);
        }
        // 衝突検知
        if (CheckCollisionWithGround()) {
            Destroy(); // 破壊処理
        }
    }
}

float Snowman::GetFrictionRasistance()
{
    return frictionRasistance;
}

bool Snowman::CheckCollisionWithGround()
{

}


void Snowman::Destroy()
{
    // オブジェクトの破壊処理
}
