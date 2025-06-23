#include "pch.h"
#include "Actor.h"
#include "MoveComp.h"
#include "GoalComp.h"
#include "DrawComp.h"
#include "Goal/Base/Goal.h"
#include "Goal/Base/Goal_Think.h"
#include "Goal_ChangeDir.h"

const char* Goal_ChangeDir::GOAL_NAME = "Goal_ChangeDir";


Goal_ChangeDir::Goal_ChangeDir(Actor* actor, ax::Vec2 dest)
    : Goal(actor,GoalType::AnimChange) {

    m_Dest = dest;
}

void Goal_ChangeDir::Start()
{
    m_Status                        = Goal::active_t;
    mActor->mGoalComp->mCurGoal = GoalType::AnimChange;
    mActor->mUnitComp->ChangeAction(ActionState::Idle);
    ax::Vec2 velocity = m_Dest / m_Dest.getLength();
    mActor->mDrawComp->mCurDir = mActor->mDrawComp->CalcAniDir(velocity);
}

int Goal_ChangeDir::Do()
{
    If_Inactive_Start();

    m_Status = Goal::completed_t;

    return m_Status;
}

void Goal_ChangeDir::End() {

}

