#include "pch.h"
#include "Actor.h"
#include "MoveComp.h"
#include "GoalComp.h"
#include "UnitComp.h"
#include "Goal/Base/Goal.h"
#include "Goal/Base/Goal_Think.h"
#include "Goal_WaitTime.h"
#include "../../DrawComp.h"

const char* Goal_WaitTime::GOAL_NAME = "Goal_WaitTime";
Goal_WaitTime::Goal_WaitTime(Actor* actor)
    : Goal(actor,GoalType::WaitTime) {

    int idx;
    srand(time(NULL));
    idx      = rand() % 3 + 2;
    randTime = (float)idx;
}

void Goal_WaitTime::Start()
{
    m_Status                        = Goal::active_t;
    mActor->mGoalComp->mCurGoal = GoalType::WaitTime;

    mActor->mMoveComp->Start_ElapsedTime();
    auto node = mActor->mDrawComp->CreateGatheringNode(mActor->mActorType);
    node->setPosition(mActor->mDrawComp->GetCarryItemPos(mActor->mDrawComp->mCurDir));
}

int Goal_WaitTime::Do()
{
    If_Inactive_Start();

    if (mActor->mMoveComp->mTimer > randTime)
    {
        m_Status = Goal::completed_t;
        mActor->mUnitComp->mCurAction = ActionState::Idle;
        auto gatherNode               = mActor->GetRoot()->getChildByName("GatherAnim");
        gatherNode->removeFromParentAndCleanup(true);
        return m_Status;
    }

    return m_Status;
}

void Goal_WaitTime::End()
{
    mActor->mMoveComp->Stop_ElapsedTime();
    __super::End();
}

bool Goal_WaitTime::isStuck() const
{

    return false;
}
