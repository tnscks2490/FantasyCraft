#pragma once
#include "Goal/Base/Goal.h"
#include "Goal/Base/Goal_Think.h"

class Goal_WaitTime : public Goal
{
public:
    static const char* GOAL_NAME;
    Goal_WaitTime(Actor* actor);

    virtual void Start() override;
    virtual int Do() override;
    virtual void End() override;

    const char* getName() override { return GOAL_NAME; }
    bool isStuck() const;


public:

    double mExpectedTime;
    ax::Vec2 m_Dest;
};


