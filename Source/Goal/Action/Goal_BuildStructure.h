#pragma once
#include "Actor.h"
#include "Goal/Base/Goal_Composite.h"
#include "Goal/Base/Goal_Think.h"

class Goal_BuildStructure : public Goal
{
public:
    static const char* GOAL_NAME;
    Goal_BuildStructure(Actor* actor, ActorType type);

    virtual void Start() override;
    virtual int Do() override;
    virtual void End() override;

    const char* getName() override { return GOAL_NAME; }

public:

    double mExpectedTime;
    ax::Vec2 m_Dest;

    ActorType mStructure;
    bool isdoing = false;

};


