#include "pch.h"
#include "Actor.h"
#include "MoveComp.h"
#include "GoalComp.h"
#include "PathFind.h"
#include "UnitComp.h"
#include "SensorComp.h"
#include "Goal/Base/Goal.h"
#include "Goal/Base/Goal_Think.h"
#include "Goal_ApproachToLocation.h"

const char* Goal_ApproachToLocation::GOAL_NAME = "Goal_ApproachToLocation";
Goal_ApproachToLocation::Goal_ApproachToLocation(Actor* actor, ax::Vec2 dest)
    : Goal(actor,GoalType::Approach) {

     mTargetDest = dest;
     mApproDest = World::get()->mPath->FindEmptyTileNearActor(mActor->GetPosition(), mTargetDest);
}

void Goal_ApproachToLocation::Start()
{
    m_Status                        = Goal::active_t;
    mActor->mGoalComp->mCurGoal = GoalType::Approach;

    if (mActor->mMoveComp)
        mActor->mMoveComp->SetPath(mApproDest);

     mActor->mUnitComp->mCurAction = ActionState::Move;
}

int Goal_ApproachToLocation::Do()
{
    If_Inactive_Start();

    if (mActor->mMoveComp->IsArriveComplete())
    {
        m_Status = Goal::completed_t;
        mActor->mUnitComp->mCurAction = ActionState::Idle;
        return m_Status;
    }

    return m_Status;
}

void Goal_ApproachToLocation::End() {

}
