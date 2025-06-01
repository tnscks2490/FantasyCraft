#include "pch.h"
#include "Actor.h"
#include "MoveComp.h"
#include "GoalComp.h"
#include "UnitComp.h"
#include "Goal/Base/Goal.h"
#include "Goal/Base/Goal_Think.h"
#include "Goal_GiveResource.h"

const char* Goal_GiveResource::GOAL_NAME = "Goal_GiveResource";
Goal_GiveResource::Goal_GiveResource(Actor* actor,Actor* cargo)
    : Goal(actor,GoalType::Gather) {
    mCargo = cargo;
}

void Goal_GiveResource::Start()
{
    m_Status                        = Goal::active_t;
    mActor->mGoalComp->mCurGoal = GoalType::Gather;

    ActorMessage msg = {MsgType::GiveResource, mCargo, nullptr, nullptr};
    SendActorMessage(mActor, msg);

}

int Goal_GiveResource::Do()
{
    If_Inactive_Start();

    m_Status = Goal::completed_t;

    return m_Status;
}

void Goal_GiveResource::End() {
 
}

