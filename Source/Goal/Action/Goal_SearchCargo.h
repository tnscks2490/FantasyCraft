#pragma once
#include "Goal/Base/Goal.h"
#include "Goal/Base/Goal_Think.h"

class Goal_SearchCargo : public Goal
{
public:
    static const char* GOAL_NAME;
    Goal_SearchCargo(Actor* actor);

    virtual void Start() override;
    virtual int Do() override;
    virtual void End() override;

    const char* getName() override { return GOAL_NAME; }



public:

};


