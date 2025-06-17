#pragma once
#include "IActorComp.h"


class SensorMemory;

class SensorComp : public IActorComp
{
public:
    SensorComp(Actor* actor);
    ~SensorComp();

    virtual void update(float delta) override;
    virtual void MessageProc(ActorMessage& msg) override;

    void SetSight(float sight) { mSight = sight*32; }

    void SetSightByType(ActorType type);
    void ReStartSensor();


    ax::Node* CreateSightNode();

public:


    float mSight = 0;

    Actor* mTarget              = nullptr;

    SensorMemory* mSenserMemory = nullptr;
};

