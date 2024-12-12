#pragma once
#include "UnitComp.h"





class SCVComp : public UnitComp
{
public:
    SCVComp(Actor* actor);
    ~SCVComp();

    virtual void update(float delta) override;

    void Repair();
    void Building();



public:
    bool IsBuilding = false;
    bool IsReparing = false;
    short mPop      = 1;
};
