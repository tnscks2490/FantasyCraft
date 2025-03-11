#pragma once
#include "Goal/Base/Goal.h"
#include "Goal/Base/Goal_Think.h"
#include "PathFind.h"

class Goal_MoveToPath : public Goal
{
public:
    static const char* GOAL_NAME;
    Goal_MoveToPath(Actor* actor, ax::Vec2 dest);

    virtual void Start() override;
    virtual int Do() override;
    virtual void End() override;

    const char* getName() override { return GOAL_NAME; }

public:

    double mExpectedTime;
    ax::Vec2 mLastDest;
};


