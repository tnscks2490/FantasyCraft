#pragma once
#include "UnitComp.h"





class SCVComp : public UnitComp
{
public:
    SCVComp(Actor* actor);
    ~SCVComp();

    virtual void MessageProc(ActorMessage& msg) override;
    virtual void update(float delta) override;
    void Building(ActorMessage& msg);
    void Repair();


    void Gathering(Actor* resource);
    void GiveMineral();
    void SCVHpChange();
    void Build_Continue(ActorMessage& msg);

    


public:
    float mTimer    = 0;
    bool IsWorking = false;
    short mPop      = 1;

    
    GetItem mItem = GetItem::None;

    Actor* mBuilding   = nullptr;
    Actor* mGatherResource    = nullptr;
    Actor* mHomeCenter = nullptr;
    
};
