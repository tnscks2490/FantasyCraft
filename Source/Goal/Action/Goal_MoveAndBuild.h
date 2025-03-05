#pragma once
#include "Actor.h"
#include "Goal/Base/Goal_Composite.h"
#include "Goal/Base/Goal_Think.h"

class Goal_MoveAndBuild : public Goal_Composite
{
public:

    Goal_MoveAndBuild(Actor* actor, ax::Vec2 dest,ActorType type);

    virtual void Start() override;
    virtual int Do() override;
    virtual void End() override;

public:

    double mExpectedTime;
    ax::Vec2 m_Dest;

    ActorType mStructure;

};


