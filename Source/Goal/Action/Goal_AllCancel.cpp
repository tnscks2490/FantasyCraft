#include "pch.h"
#include "Actor.h"
#include "MoveComp.h"
#include "GoalComp.h"
#include "UnitComp.h"
#include "Goal/Base/Goal.h"
#include "Goal/Base/Goal_Think.h"
#include "Goal_AllCancel.h"

const char* Goal_AllCancel::GOAL_NAME = "Goal_AllCancel";


Goal_AllCancel::Goal_AllCancel(Actor* actor)
    : Goal(actor,GoalType::Cancel)
{

}

void Goal_AllCancel::Start()
{
    m_Status                        = Goal::active_t;
    mActor->mGoalComp->mCurGoal = GoalType::Cancel;
    mActor->mUnitComp->mCurAction   = ActionState::Idle;
}

int Goal_AllCancel::Do()
{
    If_Inactive_Start();

    m_Status = Goal::completed_t;
    mActor->mGoalComp->mCurGoal = GoalType::None;


    return m_Status;
}

void Goal_AllCancel::End()
{
    __super::End();
}
