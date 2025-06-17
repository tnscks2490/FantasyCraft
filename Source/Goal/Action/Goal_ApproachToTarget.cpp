#include "pch.h"
#include "Actor.h"
#include "MoveComp.h"
#include "GoalComp.h"
#include "PathFind.h"
#include "UnitComp.h"
#include "SensorComp.h"
#include "Goal/Base/Goal.h"
#include "Goal/Base/Goal_Think.h"
#include "Goal_ApproachToTarget.h"

const char* Goal_ApproachToTarget::GOAL_NAME = "Goal_ApproachToTarget";
Goal_ApproachToTarget::Goal_ApproachToTarget(Actor* actor,ax::Vec2 dest)
    : Goal(actor,GoalType::Approach) {

     mTargetDest = dest;
}

void Goal_ApproachToTarget::Start()
{
    m_Status                        = Goal::active_t;
    mActor->mGoalComp->mCurGoal = GoalType::Approach;

    if (mActor->mMoveComp)
        mActor->mMoveComp->SetPath(mTargetDest);

     mActor->mUnitComp->mCurAction = ActionState::Move;
}

int Goal_ApproachToTarget::Do()
{
    If_Inactive_Start();

    auto len   = length(mActor->GetPosition(), mTargetDest);
    auto range = mActor->mWeaponComp->GetRange();

    if ( len < range)
    {
        m_Status = Goal::completed_t;
        mActor->mMoveComp->StopMove();
        mActor->mUnitComp->mCurAction = ActionState::Idle;
        return m_Status;
    }

    return m_Status;
}

void Goal_ApproachToTarget::End()
{
    __super::End();
}
