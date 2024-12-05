#include "pch.h"

#include "MoveComp.h"
#include "DrawComp.h"
#include "Actor.h"
#include "PathFind.h"


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
        mCurFrameMovement = mVelocity * delta * mSpeed;
        pos += mCurFrameMovement;
        mActor->GetRoot()->setPosition(pos);
        UpdateBodyRect();
    }
}

std::list<jpspath::Coord> MoveComp::PathSearch(PathFind* path, ax::Vec2 targetPos)
{
    std::list<jpspath::Coord> ResultNodes;
    jpspath::Path jps;
    jps.Init(path->mColMap);

    int32_t sx = mActor->GetRoot()->getPosition().x / 16;
    int32_t sy = mActor->GetRoot()->getPosition().y / 16;
    int32_t ex = targetPos.x / 16;
    int32_t ey = targetPos.y / 16;

    jps.Search(sx, sy, ex, ey, ResultNodes);
    return ResultNodes;
}

bool MoveComp::IsArrive()
{
    ax::Vec2 mypos  = mActor->GetRoot()->getPosition();
    ax::Vec2 target = mTarget;

    float m = length(mActor->GetRoot()->getPosition(), mTarget);
    
    if (1.0 > m)
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

void MoveComp::UpdateBodyRect()
{
    mBodyBorder.left = mActor->GetPosition().x - 8.f;
    mBodyBorder.right = mActor->GetPosition().x + 8.f;
    mBodyBorder.bottom = mActor->GetPosition().y - 8.f;
    mBodyBorder.top    = mActor->GetPosition().y + 8.f;
}

//void MoveComp::IfCollisionMove(Border other)
//{
//    float Left   = mBodyBorder.left - other.right;
//    float Right  = other.left - mBodyBorder.right;
//    float Top    = mBodyBorder.top - other.bottom;
//    float Bottom = other.top - mBodyBorder.bottom;
//
//
//    if (Right <= 0 && Left <= 0 && Top <= 0 && Bottom <= 0)
//    {
//        if (Right >= Left && Right >= Top && Right >= Bottom)
//        {
//            float sx = mActor->GetPosition().x + Right;
//            if (mActor->mMoveComp->mTargetList.size() < 1)
//                mActor->mMoveComp->mTargetList.emplace_front(ax::Vec2(sx, mActor->GetPosition().y));
//            else
//            { 
//                  mActor->mMoveComp->mTarget = ax::Vec2(sx, mActor->GetPosition().y);
//            }
//        }
//        else if (Left >= Right && Left >= Top && Left >= Bottom)
//        {
//            float sx = mActor->GetPosition().x - Left;
//            if (mActor->mMoveComp->mTargetList.size() < 1)
//                mActor->mMoveComp->mTargetList.emplace_front(ax::Vec2(sx, mActor->GetPosition().y));
//            else
//            {
//                mActor->mMoveComp->mTarget = ax::Vec2(sx, mActor->GetPosition().y);
//            }
//        }
//        else if (Top >= Right && Top >= Left && Top >= Bottom)
//        {
//            float sy = mActor->GetPosition().y - Top;
//            if (mActor->mMoveComp->mTargetList.size() < 1)
//                mActor->mMoveComp->mTargetList.emplace_front(ax::Vec2(mActor->GetPosition().x, sy));
//            else
//            {
//                mActor->mMoveComp->mTarget = ax::Vec2(mActor->GetPosition().x, sy);
//            }
//        }
//        else if (Bottom >= Right && Bottom >= Left && Bottom >= Top)
//        {
//            float sy = mActor->GetPosition().y + Bottom;
//            if (mActor->mMoveComp->mTargetList.size() < 1)
//                mActor->mMoveComp->mTargetList.emplace_front(ax::Vec2(mActor->GetPosition().x, sy));
//            else
//            {
//                mActor->mMoveComp->mTarget = ax::Vec2(mActor->GetPosition().x, sy);
//            }
//        }
//    }
//}

void MoveComp::SetTarget(ax::Vec2 target)
{
    mTarget  = target;
    IsMoving = true;
   
}

void MoveComp::SetPath(PathFind* path, ax::Vec2 targetPos)
{
    auto resultNode = PathSearch(path,targetPos);

    if (mTargetList.size() > 0)
    {
        mTargetList.clear();
    }

    if (resultNode.size() < 1)
        return;

    for (auto t : resultNode)
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
