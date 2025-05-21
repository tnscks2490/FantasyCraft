#pragma once
#include "UnitComp.h"


class MarineComp : public UnitComp
{
public:
    MarineComp(Actor* actor);
    ~MarineComp();

    virtual void update(float delta) override;
    virtual void MessageProc(ActorMessage& msg) override;


    void AttackTarget(Actor* Target);

public:
    short mPop      = 1;

    // 공격대상
    Actor* mAttackTarget = nullptr;
};
