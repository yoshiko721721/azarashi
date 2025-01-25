#pragma once
#include "../../01_Direct3D/Object.h"
#include "../../02_Input/input.h"

class BreakBlock : public Object
{
public:
    BreakBlock() {};
    BreakBlock(float posX, float posY, float sizeX, float sizeY) : Object(posX, posY, sizeX, sizeY) {};
    ~BreakBlock() { Uninit(); }

    void Init();    // ������
    void Update();  // �X�V
    void Break();   // ���鏈��
    void Respawn(); // ��������

    float GetFrictionRasistance();

private:
    bool isBroken;             // ��ꂽ���ǂ����̃t���O
    float frictionRasistance;  // ���C�W��
    float fallSpeed;           // �������x
    float respawnTimer;        // �����܂ł̎���
    const float respawnTime = 3.0f;  // �����܂ł̎��ԁi�b�j
    const float bottom = -200.0f;
    float StartPosX;
    float StartPosY;
};
