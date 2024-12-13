#include "pch.h"
#include "Goal_Composite.h"

int Goal_Composite::ProcessSubgoals()
{
    while (!m_SubGoals.empty() &&
        (m_SubGoals.front()->isComplete() || m_SubGoals.front()->isFailed()))
    {
        Goal* g = m_SubGoals.front();
        m_SubGoals.pop_front();

        g->End();
        delete g;
    }

    if (m_SubGoals.empty()) return completed_t;

    int StatusOfSubGoals = m_SubGoals.front()->Do();


    if (StatusOfSubGoals != completed_t)
        return StatusOfSubGoals;

   

    if (m_SubGoals.size() > 1)
        return active_t;

    return completed_t;
}

bool Goal_Composite::SendToFirstSubGoal(const ActorMessage& msg)
{
    if (!m_SubGoals.empty())
    {
        return m_SubGoals.front()->handleMessage(msg);
    }
    return false;
}

int Goal_Composite::Do()
{
    If_Inactive_Start();
    m_Status = ProcessSubgoals();
    return m_Status;
}

void Goal_Composite::Render(int step)
{
    __super::Render(step);
    ++step;

    for (Goal* it : m_SubGoals)
    {
        it->Render(step);
    }
}

bool Goal_Composite::handleMessage(const ActorMessage& msg)
{
    return SendToFirstSubGoal(msg);
}

void Goal_Composite::RemoveAllSubgoals()
{
    while (!m_SubGoals.empty())
    {
        Goal* g = m_SubGoals.front();
        m_SubGoals.pop_front();
        g->End();
        delete g;
    }

    m_SubGoals.clear();
}
