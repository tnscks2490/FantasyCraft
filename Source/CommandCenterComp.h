#pragma once
#include "UnitComp.h"


class CommandCenterComp : public UnitComp
{
public:
    CommandCenterComp(Actor* actor);
    ~CommandCenterComp();

    virtual void update(float delta) override;

public:


};
