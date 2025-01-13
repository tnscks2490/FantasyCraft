#pragma once
#include "Goal/Base/Goal_Composite.h"
#include "Goal/Base/Goal_Think.h"

class Goal_BuildCommandCenter : public Goal_Composite
{
public:

    Goal_BuildCommandCenter(Actor* actor, ax::Vec2 dest);

    virtual void Start() override;
    virtual int Do() override;
    virtual void End() override;

public:

    double mExpectedTime;
    ax::Vec2 m_Dest;
};


