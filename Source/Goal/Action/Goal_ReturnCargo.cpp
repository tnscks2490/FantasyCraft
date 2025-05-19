#include "pch.h"
#include "Actor.h"
#include "MoveComp.h"
#include "GoalComp.h"
#include "UnitComp.h"
#include "Goal/Base/Goal.h"
#include "Goal/Base/Goal_Think.h"
#include "Goal_ReturnCargo.h"

const char* Goal_ReturnCargo::GOAL_NAME = "Goal_ReturnCargo";
Goal_ReturnCargo::Goal_ReturnCargo(Actor* gather)
    : Goal(gather,GoalType::Gather) {

    mGather = gather;
}

void Goal_ReturnCargo::Start()
{
    m_Status                        = Goal::active_t;
    mActor->mGoalComp->mCurGoal = GoalType::Gather;

    ActorMessage msg = {MsgType::ReturnCargo, mGather, nullptr, nullptr};
    SendActorMessage(mActor, msg);
}

int Goal_ReturnCargo::Do()
{
    If_Inactive_Start();


    m_Status = Goal::completed_t;
    return m_Status;
}

void Goal_ReturnCargo::End() {
   
}
