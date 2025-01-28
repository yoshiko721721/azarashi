#include "Snowman.h"
#include "../../../08_Collider/BoxCollider.h"
#include <iostream>

void Snowman::Init() {
    Initialize(L"Asset/pic/snowman.png");   // 背景を初期化
    SetSize(100.0f, 50.0f, 0.0f);          // 大きさを設定
    SetColor(1.0f, 1.0f, 1.0f, 1.0f);      // 色を設定
    frictionResistance = 0.5f;              // 初期摩擦抵抗
    angle = 0.0f;                          // 初期角度
    isFalling = false;                     // 初期落下状態
    velocityY = 0.0f;                      // 初期速度
    rigidBody.SetMass(1.0f);                // RigidBodyに質量を設定
}

void Snowman::Update() {
    // 角度の調整を行う入力処理
    if (Input::GetKeyPress(VK_LEFT)) {
        SetAngle(GetAngle() + 3);  // 左キーが押されたら角度を増加
    }
    else if (Input::GetKeyPress(VK_RIGHT)) {
        SetAngle(GetAngle() - 3);  // 右キーが押されたら角度を減少
    }
    else if (Input::GetKeyPress(VK_SPACE)) {
        SetAngle(0);  // スペースキーが押されたら角度をリセット
    }

    // スノーマンが落下を開始するかどうかをチェック
    float currentAngle = GetAngle();
    if (currentAngle < -10.0f && !isFalling) {
        isFalling = true;  // 角度が一定の閾値を下回ったら落下を開始
    }

    // 落下の物理挙動をRigidBodyを使って更新
    if (isFalling) {
        // 重力を適用し、位置を更新
        rigidBody.FreeFall(0.016f);  // 1フレームあたり16msを仮定して物理演算
        SetPos(GetPos().x, GetPos().y - rigidBody.GetVector().y, GetPos().z);  // 速度に基づいて位置を更新

        // 衝突判定
        if (CheckCollisionWithGround()) {
            Destroy();  // 地面に衝突したらスノーマンを破壊
        }
    }
}

float Snowman::GetFrictionResistance() {
    return frictionResistance;  // 摩擦抵抗値を返す
}

bool Snowman::CheckCollisionWithGround() {
    // 単純な衝突判定（BoxColliderを使って詳細な衝突判定も可能）
    if (GetPos().y <= 0) {
        return true;  // Y座標が0以下なら衝突とみなす
    }
    return false;
}

void Snowman::Destroy() {
    // スノーマンの破壊処理
    Object::Uninit();
}
