#include "MoveComp.h"
#include "Actor.h"


MoveComp::MoveComp(Actor* actor)
    : IActorComp(actor)
{
    actor->mMoveComp = this;
}

MoveComp::~MoveComp() {}

void MoveComp::update(float delta)
{
    mVelocity = ax::Vec2(0, 0);

    mTimer += delta;

    if (mTimer > 1.0f)
    {
        mTimer = 0;
    }

    CheckTargetList();
    if (IsMoving)
    {
        Do_Moving();
        mVelocity.normalize();
        ax::Vec2 pos = mActor->mRoot->getPosition();
        pos += mVelocity * delta * mSpeed;
        mActor->mRoot->setPosition(pos);
    }
}

bool MoveComp::IsArrive()
{
    return false;
}

void MoveComp::Do_Moving() {}

void MoveComp::CheckTargetList() {}
