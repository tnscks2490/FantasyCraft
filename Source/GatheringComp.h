#pragma once
#include "UnitComp.h"
#include "Player.h"

class Actor;


class GatheringComp : public UnitComp
{
public:
    GatheringComp(Actor* actor);
    ~GatheringComp();

    void CreateSCV();
    void CreateProbe();
    void CreateDrone();

    virtual void update(float delta) override;

    void Repair();


public:
};

