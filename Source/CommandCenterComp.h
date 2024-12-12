#pragma once
#include "UnitComp.h"





class CommandCenter : public UnitComp
{
public:
    CommandCenter(Actor* actor);
    ~CommandCenter();

    virtual void update(float delta) override;

public:
    short mPop      = 1;
};
