#pragma once
#include "Actor.h"
#include "Goal/Base/Goal_Composite.h"
#include "Goal/Base/Goal_Think.h"

class Goal_BuildStructure : public Goal
{
public:

    Goal_BuildStructure(Actor* actor, ActorType type);

    virtual void Start() override;
    virtual int Do() override;
    virtual void End() override;

public:

    double mExpectedTime;
    ax::Vec2 m_Dest;

    ActorType mStructure;

};


