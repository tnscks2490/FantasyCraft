#include "pch.h"
#include "Actor.h"
#include "MoveComp.h"
#include "GoalComp.h"
#include "UnitComp.h"
#include "Goal/Base/Goal.h"
#include "Goal/Base/Goal_Think.h"
#include "Goal_Gathering.h"

const char* Goal_Gathering::GOAL_NAME = "Goal_Gathering";
Goal_Gathering::Goal_Gathering(Actor* gather,Actor* mMineral)
    : Goal(gather,GoalType::Gather) {

    mTargetResource = mMineral;
}

void Goal_Gathering::Start()
{
    m_Status                        = Goal::active_t;
    mActor->mGoalComp->mCurGoal = GoalType::Gather;

    ActorMessage msg = {MsgType::Gathering, mTargetResource, nullptr, nullptr};
    SendActorMessage(mActor, msg);
}

int Goal_Gathering::Do()
{
    If_Inactive_Start();

    if (!mActor->mUnitComp->IsCmdLocked())
    {
        m_Status = Goal::completed_t;
        //mActor->mUnitComp->mCurAction = ActionState::Idle;
        return m_Status;
    }

    return m_Status;
}

void Goal_Gathering::End()
{
   
}
