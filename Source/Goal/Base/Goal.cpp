#include "pch.h"
#include "Actor.h"
#include "Goal.h"
#include "Goal_Think.h"
#include "GoalComp.h"

void Goal::End()
{
    //AXLOG("~~~~~~~~~~~~~~~~~");
    mActor->mGoalComp->mThink->Render(1);
}

void Goal::Render(int step)
{
}
