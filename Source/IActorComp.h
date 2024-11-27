#pragma once
#include "axmol.h"


class Actor;

class IActorComp
{
public:
    IActorComp(Actor* actor) { mActor = actor; }
    ~IActorComp();

    virtual void update(float delta) {}
    Actor* mActor;
};

