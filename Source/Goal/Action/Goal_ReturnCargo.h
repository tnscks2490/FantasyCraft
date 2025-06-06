#pragma once
#include "Goal/Base/Goal_Composite.h"
#include "Goal/Base/Goal_Think.h"

class Goal_ReturnCargo : public Goal_Composite
{
public:
    static const char* GOAL_NAME;
    Goal_ReturnCargo(Actor* mActor,Actor* cargo);

    virtual void Start() override;
    virtual int Do() override;
    virtual void End() override;

    const char* getName() override { return GOAL_NAME; }


public:
    Actor* mCargo  = nullptr;
};


