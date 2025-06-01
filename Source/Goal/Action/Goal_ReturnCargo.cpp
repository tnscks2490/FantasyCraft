#include "pch.h"
#include "Actor.h"
#include "MoveComp.h"
#include "GoalComp.h"
#include "UnitComp.h"
#include "Goal/Base/Goal.h"
#include "Goal/Base/Goal_Think.h"
#include "Goal/Base/All_Goals.h"
#include "Goal_ReturnCargo.h"

const char* Goal_ReturnCargo::GOAL_NAME = "Goal_ReturnCargo";
Goal_ReturnCargo::Goal_ReturnCargo(Actor* mActor,Actor* cargo)
    : Goal_Composite(mActor,GoalType::Gather) {
    mCargo = cargo;
}

void Goal_ReturnCargo::Start()
{
    m_Status                        = Goal::active_t;
    mActor->mGoalComp->mCurGoal = GoalType::Gather;

    PushSubGoal(new Goal_ApproachToLocation(mActor, mCargo->GetPosition()));
    PushSubGoal(new Goal_GiveResource(mActor,mCargo));

}

int Goal_ReturnCargo::Do()
{
    If_Inactive_Start();

    m_Status = ProcessSubgoals();

    return m_Status;
}

void Goal_ReturnCargo::End() {
   
}
