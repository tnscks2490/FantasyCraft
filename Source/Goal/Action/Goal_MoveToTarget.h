#pragma once
#include "Goal/Base/Goal.h"
#include "Goal/Base/Goal_Think.h"

class Goal_MoveToTarget : public Goal
{
public:

    Goal_MoveToTarget(Actor* actor, ax::Vec2 dest);

    virtual void Start() override;
    virtual int Do() override;
    virtual void End() override;

    bool isStuck() const;

public:

    double mExpectedTime;
    ax::Vec2 m_Dest;
};


