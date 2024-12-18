#pragma once
#include "Goal/Base/Goal.h"
#include "Goal/Base/Goal_Think.h"
#include "PathFind.h"

class Goal_MoveToPath : public Goal
{
public:

    Goal_MoveToPath(Actor* actor, PathFind* path, ax::Vec2 dest);

    virtual void Start() override;
    virtual int Do() override;
    virtual void End() override;

public:

    double mExpectedTime;
    ax::Vec2 mLastDest;
};


