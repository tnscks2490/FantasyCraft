#pragma once
#include "IActorComp.h"


class Actor;

class MoveComp : public IActorComp
{
public:
    MoveComp(Actor* actor);
    ~MoveComp();

    virtual void update(float delta) override;


    bool IsArrive();
    void Do_Moving();
    void CheckTargetList();

public:

    bool IsMoving     = false;
    bool IsPathMoving = false;

    std::list<ax::Vec2> mTargetList;

    ax::Vec2 mTarget;
    ax::Vec2 mVelocity;
    float mSpeed = 100.0f;
    float mTimer = 0.f;


};

