#pragma once
#include "IActorComp.h"
#include "JPSPathFinder.h"

class Actor;
class PathFind;

class MoveComp : public IActorComp
{
public:
    MoveComp(Actor* actor);
    ~MoveComp();

    virtual void update(float delta) override;

    std::list<jpspath::Coord> PathSearch(PathFind* path, ax::Vec2 targetPos);

    void SetTarget(ax::Vec2 target);
    void SetPath(PathFind* path, ax::Vec2 targetPos);
    float length(ax::Vec2 v1, ax::Vec2 v2);
    ax::Vec2 Vec2DNormalized(ax::Vec2 target);
    bool IsArrive();
    void Do_Moving();
    void CheckTargetList();

public:
    //멤버 변수

    bool IsMoving     = false;
    bool IsPathMoving = false;

    std::list<ax::Vec2> mTargetList;

    ax::Vec2 mTarget;
    ax::Vec2 mVelocity;
    ax::Vec2 mCurFrameMovement;

public:
    //정해진 값
    float mSpeed = 100.0f;
    float mTimer = 0.f;
};

