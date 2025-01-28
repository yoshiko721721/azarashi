#pragma once
#include "../../../01_Direct3D/Object.h"
#include "../../RigidBody.h"

class Stone : public Object {
public:
    Stone();
    ~Stone();

    void Update() override;
    void SetRigidBody(RigidBody* body);
    RigidBody* GetRigidBody();

private:
    RigidBody* rigidBody;
};
