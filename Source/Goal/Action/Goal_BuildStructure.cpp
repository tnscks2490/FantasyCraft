#include "pch.h"
#include "Actor.h"
#include "MoveComp.h"
#include "GoalComp.h"
#include "UnitComp.h"
#include "Goal/Base/Goal_Composite.h"
#include "Goal/Base/Goal_Think.h"
#include "Goal_BuildStructure.h"


const char* Goal_BuildStructure::GOAL_NAME = "Goal_BuildStructure";
Goal_BuildStructure::Goal_BuildStructure(Actor* actor, ActorType type)
    : Goal(actor, GoalType::Build)
{
    mStructure = type;

}

void Goal_BuildStructure::Start()
{
    m_Status                        = Goal::active_t;
    mActor->mGoalComp->mCurGoal   = GoalType::Build;

    /*ActorMessage msg;
    msg.msgType = MsgType::Do_Build;
    msg.sender  = mActor;
    msg.data    = &mStructure;
    SendActorMessage(mActor, msg);*/
    if (TcpClient::get()->GetID() == mActor->GetID())
    {
        PEvent event = {EventType::AddUnit, 0, 0, true, mActor, mStructure};
        SendEvent(event);
    }
    

    printf("Goal_BuildStructure 들어옴\n");
    isdoing = true;
}

int Goal_BuildStructure::Do()
{
    If_Inactive_Start();

    if (isdoing)
    {
        m_Status = Goal::completed_t;
        return m_Status;
    }

    return m_Status;
}

void Goal_BuildStructure::End()
{
    __super::End();
}

