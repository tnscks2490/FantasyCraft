#include "pch.h"
#include "Goal_Think.h"
#include "Actor.h"

const char* Goal_Think::GOAL_NAME = "Goal_Think";

Goal_Think::Goal_Think(Actor* pE)
    :Goal_Composite(pE,GoalType::Think)
{

}

void Goal_Think::SelectTactic()
{
    double best = 0;
    Goal_Evaluator* MostDesirable = 0;

    for (Goal_Evaluator* it : m_Evaluators)
    {
        double desirability = it->CalculateDesirability(mActor);

        if (desirability >= best)
        {
            best = desirability;
            MostDesirable = it;
        }
    }

    if (best > 0.5)
        MostDesirable->SetGoal(mActor);
}

void Goal_Think::Start()
{
    SelectTactic();
    m_Status = Goal::active_t;
}

int Goal_Think::Do()
{
    If_Inactive_Start();

    m_Status = ProcessSubgoals();
    if (m_Status == Goal::completed_t || m_Status == Goal::failed_t || m_Status == Goal::allcompleted_t)
        End();

    return m_Status;
}

void Goal_Think::End()
{
    RemoveAllSubgoals();
    __super::End();
}

