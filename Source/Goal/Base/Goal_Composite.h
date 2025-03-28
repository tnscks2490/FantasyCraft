#pragma once
#include "preDefines.h"
#include "Goal_Types.h"
#include "Goal.h"


class Goal_Composite : public Goal
{
    typedef std::list<Goal* > SubgoalList;

public:
    SubgoalList m_SubGoals;

    int ProcessSubgoals();

public:
    Goal_Composite(Actor* pE, GoalType type) : Goal(pE, type) {}
    ~Goal_Composite() { RemoveAllSubgoals(); }

    virtual int Do() override;

    virtual void Render(int step) override;



    void AddSubGoal(Goal* g) { m_SubGoals.push_front(g); }
    void PushSubGoal(Goal* g) { m_SubGoals.push_back(g); }
    void RemoveAllSubgoals();
};
