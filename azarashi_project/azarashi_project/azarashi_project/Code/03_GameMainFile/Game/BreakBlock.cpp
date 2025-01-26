#include "BreakBlock.h"
#include <chrono>

void BreakBlock::Init()
{
    // ����������
    Initialize(L"Asset/pic/Box.png");   // �w�i��������
    SetSize(600.0f, 50.0f, 0.0f);       // �傫����ݒ�
    SetAngle(90.0f);                     // �p�x��ݒ�
    SetColor(1.0f, 1.0f, 1.0f, 1.0f);   // �F��ݒ�
    isBroken = false;                    // ������Ԃł͉��Ă��Ȃ�
    fallSpeed = 0.1f;                    // �������x
    respawnTimer = 0.0f;                 // �����^�C�}�[��������

    StartPosX = GetPos().x;
    StartPosY = GetPos().y;
}

void BreakBlock::Update()
{
    
}

void BreakBlock::Break()
{
    if (isBroken)
    {
        // �����̏���
        SetPos(GetPos().x, GetPos().y - fallSpeed, 0.0f); // Y���W�𗎉�������

        // �n�ʂɒB�����畜���̏���
        if (GetPos().y <= bottom)
        {
            fallSpeed = 0.0f;  // �������x�����Z�b�g
            respawnTimer += 1.0f / 60.0f;  

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
    isBroken = false;                // ���Ă��Ȃ���Ԃɖ߂�
    respawnTimer = 0.0f;             
}

float BreakBlock::GetFrictionRasistance()
{
    return frictionRasistance;
}
