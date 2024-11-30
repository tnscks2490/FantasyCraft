#include "pch.h"

#include "MoveComp.h"
#include "DrawComp.h"
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

    CheckTargetList();
    if (IsMoving)
    {
        Do_Moving();
        mVelocity.normalize();
        ax::Vec2 pos = mActor->GetRoot()->getPosition();
        pos += mVelocity * delta * mSpeed;
        mActor->GetRoot()->setPosition(pos);
    }
}

bool MoveComp::IsArrive()
{
    ax::Vec2 mypos  = mActor->GetRoot()->getPosition();
    ax::Vec2 target = mTarget;

    float m = length(mActor->GetRoot()->getPosition(), mTarget);
    
    if (3.0 > m)
    {
        return true;
    }
    else
        return false;
}

void MoveComp::Do_Moving()
{
    if (IsArrive())
    {
        IsMoving = false;
    }
    else
    {
        ax::Vec2 actorpos = mActor->GetRoot()->getPosition();
        mVelocity += mSpeed * Vec2DNormalized(mTarget - actorpos);
    }
}

void MoveComp::CheckTargetList()
{
    if (mTargetList.size() < 1)
    {
        return;
    }

    if (!IsMoving)
    {
        ax::Vec2 pos = mTargetList.front();
        mTargetList.pop_front();
        SetTarget(pos);
    }
}

void MoveComp::SetTarget(ax::Vec2 target)
{
    mTarget  = target;
    IsMoving = true;
   
}

void MoveComp::SetPath(std::list<jpspath::Coord> ResultNodes)
{
    if (mTargetList.size() > 0)
    {
        mTargetList.clear();
    }

    for (auto t : ResultNodes)
    {
        ax::Vec2 pos;
        pos.x = (float)t.m_x * 16;
        pos.y = (float)t.m_y * 16;
        mTargetList.push_back(pos);
    }
    mTargetList.pop_front();
}

float MoveComp::length(ax::Vec2 v1, ax::Vec2 v2)
{
    float dx = v2.x - v1.x;
    float dy = v2.y - v1.y;

    return sqrt(dx * dx + dy * dy);
}

ax::Vec2 MoveComp::Vec2DNormalized(ax::Vec2 target)
{
    ax::Vec2 vec = target;

    double vector_length = vec.length();

    if (vector_length > 2)
    {
        vec.x /= vector_length;
        vec.y /= vector_length;
    }

    return vec;
}
