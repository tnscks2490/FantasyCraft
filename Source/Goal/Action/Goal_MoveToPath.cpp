#include "pch.h"
#include "Actor.h"
#include "MoveComp.h"
#include "UnitComp.h"
#include "GoalComp.h"
#include "Goal/Base/Goal.h"
#include "Goal/Base/Goal_Think.h"
#include "Goal_MoveToTarget.h"
#include "Goal_MoveToPath.h"

const char* Goal_MoveToPath::GOAL_NAME = "Goal_MoveToPath";
Goal_MoveToPath::Goal_MoveToPath(Actor* actor, ax::Vec2 dest)
    : Goal(actor,GoalType::MoveToPath)
{
    mLastDest = dest;

}

void Goal_MoveToPath::Start()
{
    m_Status                        = Goal::active_t;
    mActor->mGoalComp->mCurGoal = GoalType::MoveToPath;

    if (mActor->mMoveComp)
        mActor->mMoveComp->SetPath(mLastDest);


    mActor->mUnitComp->mCurAction = ActionState::Move;

    printf("Goal_MoveToPath들어옴\n");
}

int Goal_MoveToPath::Do()
{
    If_Inactive_Start();


    if (mActor->mMoveComp->IsArriveComplete())
    {
        m_Status                        = Goal::completed_t;
        mActor->mUnitComp->mCurAction = ActionState::Idle;
        return m_Status;
    }

    return m_Status;
}

void Goal_MoveToPath::End()
{
    __super::End();
}
