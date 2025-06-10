#include "UnitBluePrint.h"


UnitBluePrint g_error         = {ActorType::None, 0, 0, 0, 0.f};
UnitBluePrint g_UnitBP_SCV    = {ActorType::SCV, 13, 50, 0, 1.f};
UnitBluePrint g_UnitBP_Marine = {ActorType::Marine, 15, 50, 0, 1.f};
UnitBluePrint g_UnitBP_FireBat = {ActorType::FireBat, 15, 50, 25, 1.f};
UnitBluePrint g_UnitBP_Medic   = {ActorType::Medic, 19, 50, 25, 1.f};
UnitBluePrint g_UnitBP_Ghost   = {ActorType::Ghost, 32, 25, 75, 1.f};

UnitBluePrint& FindUnitBP(ActorType type)
{
    switch (type)
    {
    case ActorType::SCV: return g_UnitBP_SCV;
    case ActorType::Marine: return g_UnitBP_Marine;
    case ActorType::FireBat: return g_UnitBP_FireBat;
    case ActorType::Medic: return g_UnitBP_Medic;
    case ActorType::Ghost: return g_UnitBP_Ghost;
    default:
        break;
    }
    return g_error;
}
