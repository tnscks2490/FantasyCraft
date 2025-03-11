#include "pch.h"
#include "Actor.h"
#include "MoveComp.h"
#include "GoalComp.h"
#include "Goal/Base/Goal.h"
#include "Goal/Base/Goal_Think.h"
#include "Goal_WaitTime.h"

const char* Goal_WaitTime::GOAL_NAME = "Goal_WaitTime";
Goal_WaitTime::Goal_WaitTime(Actor* actor)
    : Goal(actor,GoalType::WaitTime) {


}

void Goal_WaitTime::Start()
{
    m_Status                        = Goal::active_t;
    mActor->mGoalComp->mCurGoal = GoalType::WaitTime;

    mActor->mMoveComp->Start_ElapsedTime();
}

int Goal_WaitTime::Do()
{
    If_Inactive_Start();

    if (mActor->mMoveComp->mTimer > 5.f)
    {
        m_Status = Goal::completed_t;
        return m_Status;
    }

    return m_Status;
}

void Goal_WaitTime::End()
{
    mActor->mMoveComp->Stop_ElapsedTime();
    __super::End();
}

bool Goal_WaitTime::isStuck() const
{

    return false;
}
