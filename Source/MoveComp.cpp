#include "pch.h"

#include "MoveComp.h"
#include "DrawComp.h"
#include "Actor.h"
#include "PathFind.h"
#include "World.h"


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

        //TagNeighbors(World::get()->w_ActorList,16.f);

        //ax::Vec2 force = CalcVelocity(mVelocity);

        ax::Vec2 pos = mActor->GetRoot()->getPosition();
        //mVelocity += force;
        //mVelocity.normalize();
        mCurFrameMovement = mVelocity * delta * mSpeed;
        //mHeading          = mCurFrameMovement;
        //mHeading.normalize();
        pos += mCurFrameMovement;
        mActor->GetRoot()->setPosition(pos);


        // 충돌했을때 겹치지 않게 하는 코드 
        //UpdateBodyRect();
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

    float m = length(mypos, mTarget);
    
    if (1.0 > m)
    {
        if (mTargetList.size() < 1)
        {
            int x = (int)mypos.x / 16;
            int y = (int)mypos.y / 16;
            World::get()->mPath->mColMap->SetAt(x, y);
            World::get()->mPath->DebugMap();
        }
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

ax::Vec2 MoveComp::CalcVelocity(ax::Vec2 force)
{
    force = Separation(World::get()->w_ActorList) * mWeightSeparation;

    if (!AccumulateForce(mVelocity, force))
        return mVelocity;
    force = Alignment(World::get()->w_ActorList) * mWeightAlignment;
    if (!AccumulateForce(mVelocity, force))
        return mVelocity;
    force = Cohesion(World::get()->w_ActorList) * mWeightCohesion;
    if (!AccumulateForce(mVelocity, force))
        return mVelocity;

    return force;
}

ax::Vec2 MoveComp::Separation(std::vector<Actor*>& neighbors)
{
    ax::Vec2 SteeringForce;

    for (auto aa : neighbors)
    {
        if (aa != mActor && aa->mMoveComp && aa->mMoveComp->mTag)
            
        {
            ax::Vec2 ToAgent = mActor->GetPosition() - aa->GetPosition();

            // scale the force inversely proportional to the agents distance
            // from its neighbor.
            SteeringForce += Vec2DNormalized(ToAgent) / ToAgent.length();
        }
    }
        


    return SteeringForce;
}

ax::Vec2 MoveComp::Alignment(std::vector<Actor*>& neighbors)
{
    // 이웃하는 것들의 평균 방향을 기록하기 위해 사용한다.
    ax::Vec2 AverageHeading;

    // 이웃하는 지역 내의 운반기 개수를 계수하기 위해 사용된다.
    int NeighborCount = 0;

    // 표기된 운반기 모두를 반복해서 조사하고 방향 벡터들의 합을 구한다.
    for (auto aa : neighbors)
    {

        // 이 에이전트가 계산에 확실하게 포함되지 않았으며
        // 조사되고 있는 에이전트가 충분히 가까운지 확인한다.
        if ((aa != mActor) && aa->mMoveComp && aa->mMoveComp->mTag)
        //&&aa != mActor->mBehaviorComp->mPursuer)
        {
            AverageHeading += aa->mMoveComp->mHeading;

            ++NeighborCount;
        }
        // if the neighborhood contained one or more vehicles, average their
        // heading vectors.
        if (NeighborCount > 0)
        {
            AverageHeading.x /= (float)NeighborCount;
            AverageHeading.y /= (float)NeighborCount;


            AverageHeading -= mActor->mMoveComp->mHeading;
        }

        return AverageHeading;
    }
}

ax::Vec2 MoveComp::Cohesion(std::vector<Actor*>& neighbors)
{
    // first find the center of mass of all the agents
    ax::Vec2 CenterOfMass, SteeringForce;

    int NeighborCount = 0;

    for (auto aa : neighbors)
    {
        // make sure *this* agent isn't included in the calculations and that
        // the agent being examined is close enough ***also make sure it doesn't
        // include the evade target ***
        if (aa != mActor && aa->mMoveComp && aa->mMoveComp->mTag)
        {
            CenterOfMass += aa->GetPosition();

            ++NeighborCount;
        }
    }

    if (NeighborCount > 0)
    {
        // the center of mass is the average of the sum of positions
        CenterOfMass.x  /= (float)NeighborCount;
        CenterOfMass.y /= (float)NeighborCount;
        // now seek towards that position
        ax::Vec2 DesiredVelocity = Vec2DNormalized(CenterOfMass - mActor->GetPosition()) * mSpeed;

        //SteeringForce = Seek(CenterOfMass);
        SteeringForce = DesiredVelocity;
    }

    // the magnitude of cohesion is usually much larger than separation or
    // allignment so it usually helps to normalize it.
    return Vec2DNormalized(SteeringForce);
}

void MoveComp::TagNeighbors(std::vector<Actor*> ActorList, double radius)
{

    for (auto aa : ActorList)
    {
        if (aa && aa->mMoveComp)
            aa->mMoveComp->mTag = false;

        ax::Vec2 to = aa->GetPosition() - mActor->GetPosition();

        double range = radius + 16.f;  // 엑터의 가로사이즈 actor->mBoundingRadius;

        if ((aa != mActor) && (to.length() < range * range))
        {
            if (aa && aa->mMoveComp)
                aa->mMoveComp->mTag = true;
        }
    }
}

bool MoveComp::AccumulateForce(ax::Vec2 RunningTot, ax::Vec2 ForceToAdd)
{
    double MagnitudeSoFar = RunningTot.length();

    // 최대값까지 남은 값
    double MagnitudeRemaining = mMaxForce - MagnitudeSoFar;

    // 최대값보다 크면 false를 값을 더하지 않고 리턴
    if (MagnitudeRemaining <= 0.0)
        return false;

    // 더해질 힘의 크기
    double MagnitudeToAdd = ForceToAdd.length();

    // 더해지는 값이 남은값보다 적으면 그대로 더하고
    // 더해지는 값이 남은값보다 크면 줄여서 더한다.
    if (MagnitudeToAdd < MagnitudeRemaining)
    {
        RunningTot += ForceToAdd;
        return true;
    }
    else
    {
        // 힘이 최대이니 false를 리턴한다.
        RunningTot += (Vec2DNormalized(ForceToAdd) * MagnitudeRemaining);

        return true;
    }
}

bool MoveComp::IsContacted(Border other)
{
    if ((mBodyBorder.right > other.left)
        && (other.right > mBodyBorder.left)
        && (mBodyBorder.top > other.bottom)
        && (other.top > mBodyBorder.bottom))
        return true;
    else
        return false;
}

void MoveComp::Avoid()
{

    if (mTargetList.size() == 0)
    {
        if (IsMoving)
            mTargetList.emplace_back(mTarget);
    }

    ax::Vec2 pos;
    pos = mActor->GetPosition() - mCurFrameMovement;
    mTargetList.emplace_front(pos);
}

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

    int x, y;
    x = (int)mActor->GetPosition().x / 16;
    y = (int)mActor->GetPosition().y / 16;
    path->mColMap->ClrAt(x, y);
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
