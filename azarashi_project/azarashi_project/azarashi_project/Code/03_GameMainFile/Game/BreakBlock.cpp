#include "BreakBlock.h"
#include "GamePointer.h"
#include "../Application.h"
#include "../Test/Testfloor.h"
#include "../../08_Collider/BoxCollider.h"
#include <vector>
#include <chrono>

extern float gyroData[3]; // x, y, z��

void BreakBlock::Init()
{
    // ����������
    Initialize(L"Asset/pic/Box.png");   // �w�i��������
    //SetSize(600.0f, 50.0f, 0.0f);       // �傫����ݒ�
    SetAngle(0.0f);                     // �p�x��ݒ�
    SetColor(1.0f, 1.0f, 1.0f, 1.0f);   // �F��ݒ�
    isBroken = false;                    // ������Ԃł͉��Ă��Ȃ�
    fallSpeed = 2.5f;                    // �������x
    respawnTimer = 0.0f;                 // �����^�C�}�[��������

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
        // �����̏���
        SetPos(GetPos().x, GetPos().y - fallSpeed, 0.0f); // Y���W�𗎉�������

        // �n�ʂɒB�����畜���̏���
        if (GetPos().y <= StartPosY - 5)
        {
            //fallSpeed = 0.0f;  // �������x�����Z�b�g
            respawnTimer += 1.0f / 60.0f;  
            SetColor(1.0f, 1.0f, 1.0f, GetColor().w - 0.02);

            // �����܂ł̎��Ԃ��o�߂����畜��
            if (respawnTimer >= respawnTime)
            {
                Respawn();
            }
        }
    }
}

void BreakBlock::Respawn()
{
    SetPos(StartPosX, StartPosY, 0.0f); // �����ʒu�ɖ߂�
    SetColor(1.0f, 1.0f, 1.0f, 1.0f);
    std::vector<TestFloor*> floor = Application::GetInstance()->GetObjects<TestFloor>();
    SetAngle(floor[0]->nowAngle);
  
    isBroken = false;                // ���Ă��Ȃ���Ԃɖ߂�
    respawnTimer = 0.0f;             
}

float BreakBlock::GetFrictionRasistance()
{
    return frictionRasistance;
}
