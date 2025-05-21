#include "pch.h"
#include "Actor.h"
#include "MoveComp.h"
#include "GoalComp.h"
#include "UnitComp.h"
#include "Goal/Base/Goal.h"
#include "Goal/Base/Goal_Think.h"
#include "Goal/Base/All_Goals.h"
#include "Goal_MoveAndAttack.h"

const char* Goal_MoveAndAttack::GOAL_NAME = "Goal_MoveAndAttack";
Goal_MoveAndAttack::Goal_MoveAndAttack(Actor* Attacker, Actor* Target)
    : Goal_Composite(Attacker,GoalType::Attack)
{
    mTargetActor = Target;

}

void Goal_MoveAndAttack::Start()
{
    m_Status                        = Goal::active_t;
    mActor->mGoalComp->mCurGoal = GoalType::Attack;

    PushSubGoal(new Goal_ApproachToTarget(mActor, mTargetActor->GetPosition()));
    PushSubGoal(new Goal_SetTargetAndAttack(mActor, mTargetActor));

}

int Goal_MoveAndAttack::Do()
{
    If_Inactive_Start();

    m_Status = ProcessSubgoals();

    return m_Status;
}

void Goal_MoveAndAttack::End()
{
    __super::End();
}


