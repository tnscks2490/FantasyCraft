#pragma once
#include "Actor.h"
#include "Goal/Base/Goal_Composite.h"
#include "Goal/Base/Goal_Think.h"

class Goal_DoingBuild : public Goal_Composite
{
public:

    Goal_DoingBuild(Actor* actor,ax::Vec2 Dest);

    virtual void Start() override;
    virtual int Do() override;
    virtual void End() override;

public:

    double delayTime =0.f;
    ax::Vec2 m_Dest;

};


