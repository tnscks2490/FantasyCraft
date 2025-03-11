#include "pch.h"
#include "Actor.h"
#include "MoveComp.h"
#include "GoalComp.h"
#include "UnitComp.h"
#include "Goal/Base/Goal_Composite.h"
#include "Goal/Base/Goal_Think.h"
#include "Goal/Base/All_Goals.h"
#include "Goal_MoveAndBuild.h"


Goal_MoveAndBuild::Goal_MoveAndBuild(Actor* actor, ax::Vec2 dest, ActorType type)
    : Goal_Composite(actor, GoalType::Build)
{
    mStructure = type;
    m_Dest     = dest;

}

void Goal_MoveAndBuild::Start()
{
    m_Status                        = Goal::active_t;
    mActor->mGoalComp->mCurGoal   = GoalType::Build;

    if (mActor->mUnitComp->mCurAction != ActionState::Building)
    {
        PushSubGoal(new Goal_MoveToPath(mActor, m_Dest));
        PushSubGoal(new Goal_BuildStructure(mActor,mStructure));
        // 여기를 손볼것!
        PushSubGoal(new Goal_DoingBuild(mActor,m_Dest));
    }
}

int Goal_MoveAndBuild::Do()
{
    If_Inactive_Start();

    m_Status = ProcessSubgoals();

    return m_Status;
}

void Goal_MoveAndBuild::End() {}

