#pragma once
#include "../../01_Direct3D/Object.h"
#include "../../02_Input/input.h"

class BreakBlock : public Object
{
public:
    BreakBlock() {};
    BreakBlock(float posX, float posY, float sizeX, float sizeY) : Object(posX, posY, sizeX, sizeY) {};
    ~BreakBlock() { Uninit(); }

    void Init();    // 初期化
    void Update();  // 更新
    void Break();   // 壊れる処理
    void Respawn(); // 復活処理

    float GetFrictionRasistance();

private:
    bool isBroken;             // 壊れたかどうかのフラグ
    float frictionRasistance;  // 摩擦係数
    float fallSpeed;           // 落下速度
    float respawnTimer;        // 復活までの時間
    const float respawnTime = 3.0f;  // 復活までの時間（秒）
    const float bottom = -200.0f;
    float StartPosX;
    float StartPosY;
};
