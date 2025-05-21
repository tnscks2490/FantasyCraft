#pragma once
#include "Actor.h"
#include "Goal/Base/Goal_Composite.h"
#include "Goal/Base/Goal_Think.h"

class Goal_MoveAndAttack : public Goal_Composite
{
public:
    static const char* GOAL_NAME;
    Goal_MoveAndAttack(Actor* Attacker,Actor* Target);

    virtual void Start() override;
    virtual int Do() override;
    virtual void End() override;

    const char* getName() override { return GOAL_NAME; }


public:

    Actor* mTargetActor = nullptr;
};


