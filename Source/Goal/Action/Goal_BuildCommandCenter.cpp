#include "pch.h"
#include "Actor.h"
#include "MoveComp.h"
#include "GoalComp.h"
#include "Goal/Base/Goal_Composite.h"
#include "Goal/Base/Goal_Think.h"
#include "Goal_BuildCommandCenter.h"


Goal_BuildCommandCenter::Goal_BuildCommandCenter(Actor* actor, ax::Vec2 dest)
    : Goal_Composite(actor, GoalType::Build)
{


}

void Goal_BuildCommandCenter::Start()
{
    m_Status                        = Goal::active_t;
    mActor->mGoalComp->mCurGoal   = GoalType::Build;


}

int Goal_BuildCommandCenter::Do()
{
    /*If_Inactive_Start();

    if (isStuck())
    {
        m_Status = Goal::completed_t;
        return m_Status;
    }
    */
    return m_Status;
}

void Goal_BuildCommandCenter::End() {}

