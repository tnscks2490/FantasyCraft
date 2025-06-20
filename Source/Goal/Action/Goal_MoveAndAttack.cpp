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

    if (!mTargetActor->isDead)
    {
        PushSubGoal(new Goal_ApproachToTarget(mActor, mTargetActor->GetPosition()));
        PushSubGoal(new Goal_SetTargetAndAttack(mActor, mTargetActor));
    }


}

int Goal_MoveAndAttack::Do()
{
    If_Inactive_Start();

    m_Status = ProcessSubgoals();

    if (m_Status == Goal::completed_t && !mTargetActor->isDead)
    {
        PK_Data data;
        data.ClientID = mActor->GetID();
        data.input    = 132;
        data.pos      = ax::Vec2(mActor->GetIDX(), mTargetActor->GetIDX());
        TcpClient::get()->SendMessageToServer(data);


        /*ActorMessage msg = {MsgType::SetAttackTarget, mTargetActor, nullptr, nullptr};
        SendActorMessage(mActor, msg);*/
    }

    return m_Status;
}

void Goal_MoveAndAttack::End()
{
    __super::End();
}


