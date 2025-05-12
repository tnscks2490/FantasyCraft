#pragma once
#include "Goal/Base/Goal.h"
#include "Goal/Base/Goal_Think.h"

class Goal_MoveAndGathering : public Goal_Composite
{
public:
    static const char* GOAL_NAME;
    Goal_MoveAndGathering(Actor* mActor,Actor* mineral);

    virtual void Start() override;
    virtual int Do() override;
    virtual void End() override;

    const char* getName() override { return GOAL_NAME; }


public:
    Actor* mMineral = nullptr;
    ax::Vec2 m_Dest;
};


