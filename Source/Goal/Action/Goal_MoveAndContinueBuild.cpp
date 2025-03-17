#include "pch.h"
#include "Actor.h"
#include "MoveComp.h"
#include "GoalComp.h"
#include "UnitComp.h"
#include "Goal/Base/Goal_Composite.h"
#include "Goal/Base/Goal_Think.h"
#include "Goal/Base/All_Goals.h"
#include "Goal_MoveAndContinueBuild.h"

const char* Goal_MoveAndContinueBuild::GOAL_NAME = "Goal_MoveAndContinueBuild";

Goal_MoveAndContinueBuild::Goal_MoveAndContinueBuild(Actor* builder, Actor* structure)
    : Goal_Composite(builder, GoalType::Build)
{
    m_Dest = structure->GetPosition();
    m_structure = structure;
}

void Goal_MoveAndContinueBuild::Start()
{
    m_Status                        = Goal::active_t;
    mActor->mGoalComp->mCurGoal   = GoalType::Build;

    if (mActor->mUnitComp->mCurAction != ActionState::Building)
    {
        PushSubGoal(new Goal_MoveToPath(mActor, m_Dest));
        PushSubGoal(new Goal_DoingBuild(mActor, m_structure));
    }

}

int Goal_MoveAndContinueBuild::Do()
{
    If_Inactive_Start();

    m_Status = ProcessSubgoals();

    return m_Status;
}

void Goal_MoveAndContinueBuild::End() {}

