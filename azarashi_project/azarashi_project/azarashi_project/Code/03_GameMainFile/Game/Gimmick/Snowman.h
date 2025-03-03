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

    float GetFrictionResistance(); // CïRðæ¾

private:
    float frictionResistance;  // CïRl
    float angle;               // »ÝÌpx
    bool isFalling;            // ºtO
    float velocityY;           // º¬x

    RigidBody rigidBody;       // ¨®ðÇ·éRigidBody

    bool CheckCollisionWithGround(); // nÊÆÌÕË»è
    void Destroy();                  // IuWFNgÌjó
};
