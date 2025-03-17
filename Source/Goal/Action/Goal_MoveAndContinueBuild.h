#pragma once
#include "Actor.h"
#include "Goal/Base/Goal_Composite.h"
#include "Goal/Base/Goal_Think.h"

class Goal_MoveAndContinueBuild : public Goal_Composite
{
public:
    static const char* GOAL_NAME;
    Goal_MoveAndContinueBuild(Actor* builder, Actor* structure);

    virtual void Start() override;
    virtual int Do() override;
    virtual void End() override;

    const char* getName() override { return GOAL_NAME; }

public:
    ax::Vec2 m_Dest;
    Actor* m_structure = nullptr;
};


