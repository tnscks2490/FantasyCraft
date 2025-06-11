#include "pch.h"
#include "Actor.h"
#include "MoveComp.h"
#include "GoalComp.h"
#include "Goal/Base/Goal.h"
#include "Goal/Base/Goal_Think.h"
#include "Goal/Action/Goal_MoveToTarget.h"

const char* Goal_MoveToTarget::GOAL_NAME = "Goal_MoveToTarget";

Goal_MoveToTarget::Goal_MoveToTarget(Actor* actor, ax::Vec2 dest)
    : Goal(actor,GoalType::MoveToTarget) {

    m_Dest = dest;
}

void Goal_MoveToTarget::Start()
{
    m_Status                        = Goal::active_t;
    mActor->mGoalComp->mCurGoal   = GoalType::MoveToTarget;

    mActor->mMoveComp->SetTarget(m_Dest);


    mActor->mUnitComp->mCurAction = ActionState::Move;

    //stuck() 관련함 함수이므로 나중에 찾아볼것
    /*mExpectedTime = mActor->mMoveComp->getTimeToReachTarget();
    mActor->mMoveComp->Start_ElapsedTime();*/
}

int Goal_MoveToTarget::Do()
{
    If_Inactive_Start();

    if (isStuck())
    {
        m_Status = Goal::completed_t;
        return m_Status;
    }

    if (mActor->mMoveComp->IsArrive())
    {
        m_Status                        = Goal::completed_t;
        return m_Status;
    }

    return m_Status;
}

void Goal_MoveToTarget::End() {}

bool Goal_MoveToTarget::isStuck() const
{
    return false;
}
