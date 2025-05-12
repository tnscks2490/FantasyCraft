#include "pch.h"
#include "Actor.h"
#include "MoveComp.h"
#include "GoalComp.h"
#include "UnitComp.h"
#include "Goal/Base/Goal.h"
#include "Goal/Base/Goal_Think.h"
#include "Goal_Gathering.h"

const char* Goal_Gathering::GOAL_NAME = "Goal_Gathering";
Goal_Gathering::Goal_Gathering(Actor* actor)
    : Goal(actor,GoalType::Gather) {


}

void Goal_Gathering::Start()
{
    m_Status                        = Goal::active_t;
    mActor->mGoalComp->mCurGoal = GoalType::Gather;

   printf("우짜쓰까~");
}

int Goal_Gathering::Do()
{
    If_Inactive_Start();

    if (!mActor->mUnitComp->IsCmdLocked())
    {
        m_Status = Goal::completed_t;
        mActor->mUnitComp->mCurAction = ActionState::Idle;
        return m_Status;
    }

    return m_Status;
}

void Goal_Gathering::End()
{
   
}
