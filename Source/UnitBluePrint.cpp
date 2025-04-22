#include "UnitBluePrint.h"


UnitBluePrint g_error         = {ActorType::None, 0, 0, 0, 0.f};
UnitBluePrint g_UnitBP_SCV    = {ActorType::SCV, 13, 50, 0, 1.f};
UnitBluePrint g_UnitBP_Marine = {ActorType::Marine, 15, 50, 0, 1.f};








UnitBluePrint& FindUnitBP(ActorType type)
{
    switch (type)
    {
    case ActorType::SCV: return g_UnitBP_SCV;
    case ActorType::Marine: return g_UnitBP_Marine;
    default:
        break;
    }
    return g_error;
}
