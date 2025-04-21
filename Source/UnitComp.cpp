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
       break;
   case ActorType::SupplyDpot:
       break;
   case ActorType::BP:
       break;
   default:
       break;
   }
}
