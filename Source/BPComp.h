#pragma once
#include "IActorComp.h"


class BPComp : public IActorComp
{
public:
    BPComp(Actor* actor);
    ~BPComp();

    virtual void MessageProc(ActorMessage& msg) override;
    virtual void update(float delta) override;


    bool CheckBuildPossible() { return BuildPossible; }
    void ContactedUnit(ActorMessage& msg);
    void SeparatedUnit(ActorMessage& msg);



    bool BuildPossible = true;
};
