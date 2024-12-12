#pragma once
#include "UnitComp.h"





class MarineComp : public UnitComp
{
public:
    MarineComp(Actor* actor);
    ~MarineComp();

    virtual void update(float delta) override;

public:
    short mPop      = 1;
};
