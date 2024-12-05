#pragma once
#include "UnitComp.h"

class Actor;


class DetectionComp : public UnitComp
{
public:
    DetectionComp(Actor* actor) : UnitComp(actor){}
    ~DetectionComp();


    virtual void update(float delta) override;



public:
};

