#include "pch.h"
#include "Actor.h"
#include "MoveComp.h"
#include "GoalComp.h"
#include "Goal/Base/Goal.h"
#include "Goal/Base/Goal_Think.h"
#include "Goal_MoveToTarget.h"
#include "Goal_MoveToPath.h"


Goal_MoveToPath::Goal_MoveToPath(Actor* actor, PathFind* path, ax::Vec2 dest)
    : Goal_Composite(actor,GoalType::MoveToPath)
{
    mLastDest = dest;

}

void Goal_MoveToPath::Start()
{
    m_Status                        = Goal::active_t;
    mActor->mGoalComp->mCurGoal = GoalType::MoveToPath;


    // 고민을 해야할 필요가 있다.

}

int Goal_MoveToPath::Do()
{
    If_Inactive_Start();

    /*if (isStuck())
    {
        m_Status = Goal::completed_t;
        return m_Status;
    }*/

    if (mActor->mMoveComp->IsArrive())
    {
        m_Status                        = Goal::completed_t;
        return m_Status;
    }

    return m_Status;
}

void Goal_MoveToPath::End() {}
