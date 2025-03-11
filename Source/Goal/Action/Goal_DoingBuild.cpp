#include "pch.h"
#include "Actor.h"
#include "MoveComp.h"
#include "GoalComp.h"
#include "UnitComp.h"
#include "Goal/Base/Goal_Composite.h"
#include "Goal/Base/All_Goals.h"
#include "Goal/Base/Goal_Think.h"
#include "Goal_DoingBuild.h"

const char* Goal_DoingBuild::GOAL_NAME = "Goal_DoingBuild";
Goal_DoingBuild::Goal_DoingBuild(Actor* actor, ax::Vec2 Dest)
    : Goal_Composite(actor, GoalType::Build)
{
    m_Dest = Dest;
}

void Goal_DoingBuild::Start()
{
    m_Status                        = Goal::active_t;
    mActor->mGoalComp->mCurGoal   = GoalType::Build;

    
    ax::Vec2 randPos = GetRandomPosToBuild(BuildingSize::Big, m_Dest);
    ax::Vec2 dest    = m_Dest + randPos;

    PushSubGoal(new Goal_MoveToPath(mActor, dest));
    PushSubGoal(new Goal_ChangeAnim(mActor, m_Dest));
    PushSubGoal(new Goal_WaitTime(mActor));
        
}

int Goal_DoingBuild::Do()
{
    If_Inactive_Start();

    m_Status = ProcessSubgoals();

    return m_Status;
}

void Goal_DoingBuild::End() {}

