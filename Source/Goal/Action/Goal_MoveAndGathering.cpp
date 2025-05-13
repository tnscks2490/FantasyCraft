#include "pch.h"
#include "Actor.h"
#include "MoveComp.h"
#include "GoalComp.h"
#include "UnitComp.h"
#include "Goal/Base/Goal_Composite.h"
#include "Goal/Base/All_Goals.h"
#include "Goal/Base/Goal.h"
#include "Goal/Base/Goal_Think.h"
#include "Goal_MoveAndGathering.h"

const char* Goal_MoveAndGathering::GOAL_NAME = "Goal_MoveAndGathering";
Goal_MoveAndGathering::Goal_MoveAndGathering(Actor* mActor, Actor* mineral)
    : Goal_Composite(mActor, GoalType::Gather)
{
    m_Dest   = mineral->GetPosition();
    mGatherResource = mineral;
    
}

void Goal_MoveAndGathering::Start()
{
    m_Status                        = Goal::active_t;
    mActor->mGoalComp->mCurGoal = GoalType::WaitTime;


    PushSubGoal(new Goal_MoveToPath(mActor, m_Dest));
    PushSubGoal(new Goal_Gathering(mActor, mGatherResource));


}

int Goal_MoveAndGathering::Do()
{
    If_Inactive_Start();

    m_Status = ProcessSubgoals();

    return m_Status;
}

void Goal_MoveAndGathering::End()
{
}

