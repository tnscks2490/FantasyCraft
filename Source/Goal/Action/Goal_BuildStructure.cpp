#include "pch.h"
#include "Actor.h"
#include "MoveComp.h"
#include "GoalComp.h"
#include "UnitComp.h"
#include "Goal/Base/Goal_Composite.h"
#include "Goal/Base/Goal_Think.h"
#include "Goal_BuildStructure.h"


Goal_BuildStructure::Goal_BuildStructure(Actor* actor, ActorType type)
    : Goal(actor, GoalType::Build)
{
    mStructure = type;

}

void Goal_BuildStructure::Start()
{
    m_Status                        = Goal::active_t;
    mActor->mGoalComp->mCurGoal   = GoalType::Build;

    ActorMessage msg;
    msg.msgType = MsgType::Do_Build;
    msg.sender  = mActor;
    msg.data    = &mStructure;
    SendActorMessage(mActor, msg);
}

int Goal_BuildStructure::Do()
{
    If_Inactive_Start();


    m_Status = Goal::completed_t;

    return m_Status;
}

void Goal_BuildStructure::End() {}

