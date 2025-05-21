#pragma once
#include "Goal/Base/Goal.h"
#include "Goal/Base/Goal_Think.h"

class Goal_SetTargetAndAttack : public Goal
{
public:
    static const char* GOAL_NAME;
    Goal_SetTargetAndAttack(Actor* Attacker, Actor* Target);

    virtual void Start() override;
    virtual int Do() override;
    virtual void End() override;

    const char* getName() override { return GOAL_NAME; }


public:
    
    Actor* mTarget = nullptr;
};


