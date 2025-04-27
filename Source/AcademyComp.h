#pragma once
#include "UnitComp.h"



class AcademyComp : public UnitComp
{
public:
    AcademyComp(Actor* actor);
    ~AcademyComp();
    virtual void MessageProc(ActorMessage& msg) override;
    virtual void update(float delta) override;
};
