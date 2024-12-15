#pragma once
#include "Actor.h"


class Actor;

class IActorComp
{
public:
    IActorComp(Actor* actor) { mActor = actor; }
    ~IActorComp();

    virtual void update(float delta) {}
    Actor* mActor;
};

