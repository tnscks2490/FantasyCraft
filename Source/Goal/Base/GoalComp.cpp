#include "pch.h"
#include "Actor.h"
#include "GoalComp.h"
#include "Goal/Base/Goal.h"
#include "Goal/Base/Goal_Think.h"
#include "Goal/Base/All_Goals.h"


GoalComp::GoalComp(Actor* actor)
    : IActorComp(actor)
{
    mThink = new Goal_Think(actor);

    actor->mGoalComp = this;
    mCurGoal         = GoalType::None;
}

GoalComp::~GoalComp()
{
    AX_SAFE_DELETE(mThink);
}


void GoalComp::update(float delta)
{
    mThink->Do();
}

void AddGoal_MoveToPath(Actor* actor,ax::Vec2 dest)
{
    if (actor->mGoalComp)
    {
        actor->mGoalComp->mThink->RemoveAllSubgoals();
        actor->mGoalComp->mThink->AddSubGoal(new Goal_MoveToPath(actor, dest));
    }
}

void PushGoal_MoveToPath(Actor* actor, ax::Vec2 dest)
{
    if (actor->mGoalComp)
        actor->mGoalComp->mThink->PushSubGoal(new Goal_MoveToPath(actor,  dest));
}

void AddGoal_BuildStructure(Actor* actor, ActorType type)
{
    if (actor->mGoalComp)
    {
        actor->mGoalComp->mThink->RemoveAllSubgoals();
        actor->mGoalComp->mThink->AddSubGoal(new Goal_BuildStructure(actor, type));
    }
}

void PushGoal_BuildStructure(Actor* actor, ActorType type)
{
    if (actor->mGoalComp)
        actor->mGoalComp->mThink->PushSubGoal(new Goal_BuildStructure(actor, type));
}

void AddGoal_MoveAndBuild(Actor* actor, ax::Vec2 dest, ActorType type)
{
    if (actor->mGoalComp)
    {
        actor->mGoalComp->mThink->RemoveAllSubgoals();
        actor->mGoalComp->mThink->AddSubGoal(new Goal_MoveAndBuild(actor, dest, type));
    }
}

void PushGoal_MoveAndBuild(Actor* actor, ax::Vec2 dest, ActorType type)
{
    if (actor->mGoalComp)
        actor->mGoalComp->mThink->PushSubGoal(new Goal_MoveAndBuild(actor,dest, type));
}

void AddGoal_DoingBuild(Actor* actor, ax::Vec2 dest)
{
    if (actor->mGoalComp)
    {
        actor->mGoalComp->mThink->RemoveAllSubgoals();
        actor->mGoalComp->mThink->AddSubGoal(new Goal_DoingBuild(actor, dest));
    }
}

void PushGoal_DoingBuild(Actor* actor, ax::Vec2 dest)
{
    if (actor->mGoalComp)
        actor->mGoalComp->mThink->PushSubGoal(new Goal_DoingBuild(actor, dest));
}
