#pragma once
#include "../../01_Direct3D/Object.h"
#include "GameBlock.h"
#include "../../02_Input/input.h"

class BreakBlock : public GameBlock
{
public:
    BreakBlock(float startX, float startY, float sizex, float sizey, float setcenterX, float setcenterY)
    {
        DirectX::XMFLOAT3 pos = { startX ,startY ,0.0f };
        DirectX::XMFLOAT3 size = { sizex ,sizey ,0.0f };

        centerX = setcenterX;
        centerY = setcenterY;

        resetPosX = startX;
        resetPosY = startY;

        SetPos(pos.x, pos.y, pos.z);
        SetSize(size.x, size.y, size.z);
    }
    BreakBlock(float posX, float posY, float sizeX, float sizeY) : GameBlock(posX, posY, sizeX, sizeY) {};
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
    const float respawnTime = 2.0f;  // 復活までの時間（秒）
    const float bottom = -200.0f;
    float StartPosX;
    float StartPosY;

    int centerX = 1;
    int centerY = 1;

    float resetPosX;
    float resetPosY;

    int breakBlockCount = 0;
};
