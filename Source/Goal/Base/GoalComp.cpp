#include "pch.h"
#include "Actor.h"
#include "GoalComp.h"
#include "Goal/Base/Goal.h"
#include "Goal/Base/Goal_Think.h"


GoalComp::GoalComp(Actor* actor)
    : IActorComp(actor)
{
    mThink = new Goal_Think(actor);

    actor->mGoalComp = this;
    mCurGoal         = GoalType::None;
}

GoalComp::~GoalComp()
{}

void GoalComp::update(float delta) {}
