#include "BuildingBluePrint.h"


BuildingBluePrint g_error      = {ActorType::None, 0, 0, 0};
BuildingBluePrint g_UnitBP_CommandCenter = {ActorType::CommandCenter, 75, 400, 0};
BuildingBluePrint g_UnitBP_SupplyDepot = {ActorType::SupplyDepot, 25, 100, 0};
BuildingBluePrint g_UnitBP_Barrack = {ActorType::Barrack, 50, 150, 0};
BuildingBluePrint g_UnitBP_Refinery   = {ActorType::Refinery, 25, 50, 0};
BuildingBluePrint g_UnitBP_EngineeringBay   = {ActorType::EngineeringBay, 38, 125, 0};

BuildingBluePrint& FindBuildingBP(ActorType type)
{
    switch (type)
    {
    case ActorType::CommandCenter: return g_UnitBP_CommandCenter;
    case ActorType::SupplyDepot: return g_UnitBP_SupplyDepot;
    case ActorType::Barrack: return g_UnitBP_Barrack;
    case ActorType::Refinery: return g_UnitBP_Refinery;
    case ActorType::EngineeringBay: return g_UnitBP_EngineeringBay;
    default:
        break;
    }
    return g_error;
}
