#include "pch.h"
#include "Actor.h"
#include "Goal.h"
#include "Goal_Think.h"
#include "GoalComp.h"

void Goal::End()
{
    AXLOG("Goal 종료: %s", getName());

    AXLOG("~~~~~~~~~~~~~~~~~");
    m_pOwner->mGoalComp->mThink->Render(1);
}

void Goal::Render(int step)
{
    char tab[] = {'\t', '\t', '\t', '\t', '\t', '\t', '\t', '\t', '\t', '\t', '\t'};
    tab[step]  = 0;
    AXLOG("%s %s", tab, getName());
}
