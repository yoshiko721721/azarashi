#include "Stone.h"
#include "../../../08_Collider/CircleCollider.h"
#include <iostream>

Stone::Stone() {
    rigidBody = new RigidBody();
}

Stone::~Stone() {
    delete rigidBody;
}

void Stone::Update() {
    // Update the physics (RigidBody) of the stone object
    rigidBody->Update();
    // You can add additional behavior specific to the Stone class here if needed
}

void Stone::SetRigidBody(RigidBody* body) {
    rigidBody = body;
}

RigidBody* Stone::GetRigidBody() {
    return rigidBody;
}
