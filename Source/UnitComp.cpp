#include "pch.h"
#include "UnitComp.h"
#include "Actor.h"


UnitComp::UnitComp(Actor* actor)
    : IActorComp(actor)
{
    actor->mUnitComp = this;
}

UnitComp::~UnitComp() {}

void UnitComp::update(float delta)
{

    if (mActor)
        mActor->mUnitComp = nullptr;
}

void UnitComp::SetUnitStatus(ActorType Atype)
{
   // 업그레이드때문에 추후에 할것

   switch (Atype)
   {
   case ActorType::None:
       break;
   case ActorType::Cursor:
       break;
   case ActorType::SCV:
       mStatus.MaxHP = 60;
       mStatus.HP = 60;
       mStatus.AT = 5;
       mStatus.RA = 1;
       mStatus.SI = 7;
       break;
   case ActorType::Marine:
       mStatus.MaxHP = 40;
       mStatus.HP = 40;
       mStatus.AT = 6;
       mStatus.RA = 4;
       mStatus.SI = 7;
       break;
   case ActorType::CommandCenter:
       mStatus.MaxHP = 1500;
       mStatus.HP    = 150;
       mStatus.DF    = 1;
       break;
   case ActorType::Barrack:
       mStatus.MaxHP = 1000;
       mStatus.HP    = 100;
       mStatus.DF    = 1;
       break;
   case ActorType::SupplyDepot:
       mStatus.MaxHP = 500;
       mStatus.HP    = 50;
       mStatus.DF    = 1;
       break;
   case ActorType::Academy:
       mStatus.MaxHP = 600;
       mStatus.HP    = 60;
       mStatus.DF    = 1;
       break;
   case ActorType::Armory:
       mStatus.MaxHP = 750;
       mStatus.HP    = 75;
       mStatus.DF    = 1;
       break;
   case ActorType::Bunker:
       mStatus.MaxHP = 350;
       mStatus.HP    = 35;
       mStatus.DF    = 1;
       break;
   case ActorType::EngineeringBay:
       mStatus.MaxHP = 850;
       mStatus.HP    = 85;
       mStatus.DF    = 1;
       break;
   case ActorType::ScienceFacility:
       mStatus.MaxHP = 850;
       mStatus.HP    = 85;
       mStatus.DF    = 1;
       break;
   case ActorType::Factory:
       mStatus.MaxHP = 1250;
       mStatus.HP    = 125;
       mStatus.DF    = 1;
       break;
   case ActorType::StarPort:
       mStatus.MaxHP = 1300;
       mStatus.HP    = 130;
       mStatus.DF    = 1;
       break;
   case ActorType::Refinery:
       mStatus.MaxHP = 750;
       mStatus.HP    = 75;
       mStatus.DF    = 1;
       break;
   case ActorType::BP:
       break;
   default:
       break;
   }
}
