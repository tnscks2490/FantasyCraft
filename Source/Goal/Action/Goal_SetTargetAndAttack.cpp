#include "pch.h"
#include "Actor.h"
#include "MoveComp.h"
#include "GoalComp.h"
#include "UnitComp.h"
#include "Goal/Base/Goal.h"
#include "Goal/Base/Goal_Think.h"
#include "Goal_SetTargetAndAttack.h"

const char* Goal_SetTargetAndAttack::GOAL_NAME = "Goal_SetTargetAndAttack";
Goal_SetTargetAndAttack::Goal_SetTargetAndAttack(Actor* Attacker, Actor* Target)
    : Goal(Attacker,GoalType::Attack)
{
    mTarget = Target;
}

void Goal_SetTargetAndAttack::Start()
{
    m_Status                        = Goal::active_t;
    mActor->mGoalComp->mCurGoal = GoalType::Attack;

    ActorMessage msg = {MsgType::AttackTarget, mTarget, nullptr, nullptr};
    SendActorMessage(mActor, msg);

}

int Goal_SetTargetAndAttack::Do()
{
    If_Inactive_Start();

    if (!mActor->mUnitComp->IsCmdLocked())
    {
        m_Status = Goal::completed_t;
        return m_Status;
    }


    return m_Status;
}

void Goal_SetTargetAndAttack::End()
{
    __super::End();
}

