#include "pch.h"
#include "Actor.h"
#include "MoveComp.h"
#include "GoalComp.h"
#include "UnitComp.h"
#include "Goal/Base/Goal_Composite.h"
#include "Goal/Base/All_Goals.h"
#include "Goal/Base/Goal_Think.h"
#include "Goal_DoingBuild.h"


Goal_DoingBuild::Goal_DoingBuild(Actor* actor, ax::Vec2 Dest)
    : Goal_Composite(actor, GoalType::Build)
{
    m_Dest = Dest;
}

void Goal_DoingBuild::Start()
{
    m_Status                        = Goal::active_t;
    mActor->mGoalComp->mCurGoal   = GoalType::Build;


    if (mActor->mUnitComp->mCurAction == ActionState::Building)
    {
        ax::Vec2 randPos = GetRandomPosToBuild(BuildingSize::Big, m_Dest);
        m_Dest += randPos*2;
        PushSubGoal(new Goal_MoveToPath(mActor, m_Dest));
    }

}

int Goal_DoingBuild::Do()
{
    If_Inactive_Start();


    m_Status = Goal::completed_t;

    return m_Status;
}

void Goal_DoingBuild::End() {}

