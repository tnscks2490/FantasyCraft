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
       mStatus.AT = 1;
       mStatus.HP = 3;
       
       break;
   case ActorType::Marine:
       mStatus.AT = 1;
       mStatus.HP = 3;
       break;
   case ActorType::CommandCenter:
       break;
   case ActorType::SupplyDpot:
       break;
   case ActorType::BP:
       break;
   default:
       break;
   }
}
