#pragma once
#include "UnitComp.h"

class Actor;


class WorkerComp : public UnitComp
{
public:
    WorkerComp(Actor* actor);
    ~WorkerComp();

    virtual void update(float delta) override;


public:
    UnitCommand mUcommand = UnitCommand::Stop;
};

