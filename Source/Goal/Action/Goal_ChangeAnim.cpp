#include "pch.h"
#include "Actor.h"
#include "MoveComp.h"
#include "GoalComp.h"
#include "DrawComp.h"
#include "Goal/Base/Goal.h"
#include "Goal/Base/Goal_Think.h"
#include "Goal_ChangeAnim.h"

const char* Goal_ChangeAnim::GOAL_NAME = "Goal_ChangeAnim";


Goal_ChangeAnim::Goal_ChangeAnim(Actor* actor,ax::Vec2 dest)
    : Goal(actor,GoalType::AnimChange) {

    m_Dest = dest;
}

void Goal_ChangeAnim::Start()
{
    m_Status                        = Goal::active_t;
    mActor->mGoalComp->mCurGoal = GoalType::AnimChange;


    mActor->mDrawComp->ChangeAnim(mActor->mDrawComp->mCurAnim, mActor->mDrawComp->mCurAction,
                                  mActor->mDrawComp->CalcAniDir(m_Dest));
}

int Goal_ChangeAnim::Do()
{
    If_Inactive_Start();

    m_Status = Goal::completed_t;

    return m_Status;
}

void Goal_ChangeAnim::End()
{

}

