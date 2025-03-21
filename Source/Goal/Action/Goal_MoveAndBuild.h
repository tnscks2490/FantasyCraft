#pragma once
#include "Actor.h"
#include "Goal/Base/Goal_Composite.h"
#include "Goal/Base/Goal_Think.h"

class Goal_MoveAndBuild : public Goal_Composite
{
public:
    static const char* GOAL_NAME;
    Goal_MoveAndBuild(Actor* actor, ax::Vec2 dest,ActorType type);

    virtual void Start() override;
    virtual int Do() override;
    virtual void End() override;

    const char* getName() override { return GOAL_NAME; }

public:

    double mExpectedTime;
    ax::Vec2 m_Dest;

    ActorType mStructure;

};


