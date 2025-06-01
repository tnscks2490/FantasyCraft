#include "pch.h"
#include "Actor.h"
#include "MoveComp.h"
#include "GoalComp.h"
#include "UnitComp.h"
#include "Goal/Base/Goal.h"
#include "Goal/Base/Goal_Think.h"
#include "Goal_SearchCargo.h"

const char* Goal_SearchCargo::GOAL_NAME = "Goal_SearchCargo";
Goal_SearchCargo::Goal_SearchCargo(Actor* actor)
    : Goal(actor,GoalType::Gather) {

}

void Goal_SearchCargo::Start()
{
    m_Status                        = Goal::active_t;
    mActor->mGoalComp->mCurGoal = GoalType::Gather;

    ActorMessage msg = {MsgType::SearchCargo, mActor, nullptr, nullptr};
    SendActorMessage(mActor, msg);
}

int Goal_SearchCargo::Do()
{
    If_Inactive_Start();

    m_Status = Goal::completed_t;

    return m_Status;
}

void Goal_SearchCargo::End()
{
}

