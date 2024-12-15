#pragma once
#include "preDefines.h"
#include "Goal_Types.h"



class Goal
{
public:
    enum { active_t, inactive_t, completed_t, failed_t, allcompleted_t};


public:
    GoalType m_iType;
    int m_Status;
    Actor* m_pOwner;



    void If_Inactive_Start() { if (isInActive()) Start(); }
    void If_Failed_Inactive() { if (isFailed()) m_Status = inactive_t; }

public:

    Goal(Actor* pE, GoalType type) : m_iType(type), m_pOwner(pE), m_Status(inactive_t) {}
    virtual ~Goal() {}

    virtual void Start() = 0;  // Goal이 시작할 때, 먼저 활성화 시키고 시작
    virtual int Do()     = 0;
    virtual void End();  // Goal이 끝날 때 호출


    virtual void Render(int step);
    virtual const char* getName() = 0;


    virtual void AddSubGoal(Goal* g) { AXLOG("adsf"); }

    bool isComplete() const { return m_Status == completed_t; }
    bool isActive() const { return m_Status == active_t; }
    bool isInActive() const { return m_Status == inactive_t; }
    bool isFailed() const { return m_Status == failed_t; }

    GoalType GetType() const { return m_iType; }
};
