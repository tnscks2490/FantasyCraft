#pragma once
#include "Actor.h"
#include "MessageSystem.h"

class Actor;

class IActorComp
{
public:
    IActorComp(Actor* actor) { mActor = actor; }
    ~IActorComp();

    virtual void MessageProc(ActorMessage& msg){}
    virtual void update(float delta) {}
    Actor* mActor;
};

