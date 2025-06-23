#pragma once
#include "UnitComp.h"


class MarineComp : public UnitComp
{
public:
    MarineComp(Actor* actor);
    ~MarineComp();

    virtual void update(float delta) override;
    virtual void MessageProc(ActorMessage& msg) override;

    void SearchNextTarget();
    void AttackTarget(Actor* Target);
    void WaitCoolTime();

public:

    // 공격대상
    Actor* mAttackTarget = nullptr;

    
};
