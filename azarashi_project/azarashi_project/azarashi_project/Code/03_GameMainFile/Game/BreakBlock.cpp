#include "BreakBlock.h"
#include "GamePointer.h"
#include "../Application.h"
#include "../Test/Testfloor.h"
#include "../../08_Collider/BoxCollider.h"
#include <vector>
#include <chrono>

extern float gyroData[3]; // x, y, z軸

void BreakBlock::Init()
{
    // 初期化処理
    Initialize(L"Asset/pic/Box.png");   // 背景を初期化
    //SetSize(600.0f, 50.0f, 0.0f);       // 大きさを設定
    SetAngle(0.0f);                     // 角度を設定
    SetColor(1.0f, 1.0f, 1.0f, 1.0f);   // 色を設定
    isBroken = false;                    // 初期状態では壊れていない
    fallSpeed = 2.5f;                    // 落下速度
    respawnTimer = 0.0f;                 // 復活タイマーを初期化

    StartPosX = GetPos().x;
    StartPosY = GetPos().y;
}

void BreakBlock::Update()
{
    Break();
    if(!isBroken)
    { 
        std::vector<GamePointer*> Player = Application::GetInstance()->GetObjects<GamePointer>();
        ContactPointVector playerToBlock = BoxCollider::ColliderWithCircle(Player[0], this);
        if (playerToBlock.checkCollision)
        {
            breakBlockCount++;
            if (breakBlockCount == 180)
            {
                isBroken = true;
                breakBlockCount = 0;
            } 
        }
        else
        {
            breakBlockCount = 0;
        }

        float difAngle = GetAngle();
        difAngle += gyroData[1];
        SetAngle(difAngle);

        CorrectPointerPosition(difAngle);
        CorrectStonePosition(difAngle);
        CorrectSnowmanPosition(difAngle);

    }
}

void BreakBlock::Break()
{
    if (isBroken)
    {
        // 落下の処理
        SetPos(GetPos().x, GetPos().y - fallSpeed, 0.0f); // Y座標を落下させる

        // 地面に達したら復活の処理
        if (GetPos().y <= StartPosY - 5)
        {
            //fallSpeed = 0.0f;  // 落下速度をリセット
            respawnTimer += 1.0f / 60.0f;  
            SetColor(1.0f, 1.0f, 1.0f, GetColor().w - 0.02);

            // 復活までの時間を経過したら復活
            if (respawnTimer >= respawnTime)
            {
                Respawn();
            }
        }
    }
}

void BreakBlock::Respawn()
{
    SetPos(StartPosX, StartPosY, 0.0f); // 初期位置に戻す
    SetColor(1.0f, 1.0f, 1.0f, 1.0f);
    std::vector<TestFloor*> floor = Application::GetInstance()->GetObjects<TestFloor>();
    SetAngle(floor[0]->nowAngle);
  
    isBroken = false;                // 壊れていない状態に戻す
    respawnTimer = 0.0f;             
}

float BreakBlock::GetFrictionRasistance()
{
    return frictionRasistance;
}
