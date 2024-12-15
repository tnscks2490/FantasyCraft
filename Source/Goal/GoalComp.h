#pragma once
#include "IActorComp.h"
#include "Goal/Base/Goal.h"
#include "Goal/Base/Goal_Think.h"

class GoalComp : public IActorComp
{
public:
    const static std::string COMPONENT_NAME;

    GoalComp(Actor* actor);
    ~GoalComp();

    virtual void update(float delta) override;


public:
    Goal_Think* mThink = nullptr;

    GoalType mCurGoal;
};


