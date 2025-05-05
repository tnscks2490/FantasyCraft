#include "pch.h"
#include "ButtonInfo.h"


using namespace ax;


//Common Icon
ButtonInfo g_ButtonInfo_TAttack = {
    "StarResource/Resource/UI/Icon/Terran/Common/Attack1.png",
    "StarResource/Resource/UI/Icon/Terran/Common/Attack2.png",
    "",
    ButtonType::TAttack, 3
};
ButtonInfo g_ButtonInfo_TMove = {
    "StarResource/Resource/UI/Icon/Terran/Common/Move1.png",
    "StarResource/Resource/UI/Icon/Terran/Common/Move2.png",
    "",
    ButtonType::TMove, 1
};
ButtonInfo g_ButtonInfo_TSetRellyPoint = {
    "StarResource/Resource/UI/Icon/Terran/Common/SetRellyPoint1.png",
    "StarResource/Resource/UI/Icon/Terran/Common/SetRellyPoint2.png",
    "",
    ButtonType::TSetRellyPoint,6
};
ButtonInfo g_ButtonInfo_TUnLoad = {
    "StarResource/Resource/UI/Icon/Terran/Common/UnLoad1.png",
    "StarResource/Resource/UI/Icon/Terran/Common/UnLoad2.png",
    "",
    ButtonType::TUnLoad,9
};
ButtonInfo g_ButtonInfo_TLoad = {
    "StarResource/Resource/UI/Icon/Terran/Common/Load1.png",
    "StarResource/Resource/UI/Icon/Terran/Common/Load2.png",
    "",
    ButtonType::TLoad,8
};
ButtonInfo g_ButtonInfo_TPatrol = {
    "StarResource/Resource/UI/Icon/Terran/Common/Patrol1.png",
    "StarResource/Resource/UI/Icon/Terran/Common/Patrol2.png",
    "", ButtonType::TPatrol,4
};
ButtonInfo g_ButtonInfo_TReturn = {
    "StarResource/Resource/UI/Icon/Terran/Common/Return1.png",
    "StarResource/Resource/UI/Icon/Terran/Common/Return2.png",
    "", ButtonType::TReturn,6
};
ButtonInfo g_ButtonInfo_THold = {
    "StarResource/Resource/UI/Icon/Terran/Common/Hold1.png",
    "StarResource/Resource/UI/Icon/Terran/Common/Hold2.png",
    "", ButtonType::THold,5
};
ButtonInfo g_ButtonInfo_TStop = {
    "StarResource/Resource/UI/Icon/Terran/Common/Stop1.png",
    "StarResource/Resource/UI/Icon/Terran/Common/Stop2.png",
    "", ButtonType::TStop,2
};
ButtonInfo g_ButtonInfo_TGather = {
    "StarResource/Resource/UI/Icon/Terran/Common/Gather1.png",
    "StarResource/Resource/UI/Icon/Terran/Common/Gather2.png",
    "", ButtonType::TGather,5
};
ButtonInfo g_ButtonInfo_TCancel = {
    "StarResource/Resource/UI/Icon/Terran/Common/Cancel1.png",
    "StarResource/Resource/UI/Icon/Terran/Common/Cancel2.png",
    "", ButtonType::TCancel,9
};
ButtonInfo g_ButtonInfo_TRepair = {
    "StarResource/Resource/UI/Icon/Terran/Common/Repair1.png",
    "StarResource/Resource/UI/Icon/Terran/Common/Repair2.png",
    "", ButtonType::TRepair,4
};
ButtonInfo g_ButtonInfo_TCommon_Build = {
    "StarResource/Resource/UI/Icon/Terran/Common/CommonBuild1.png",
    "StarResource/Resource/UI/Icon/Terran/Common/CommonBuild2.png",
    "", ButtonType::TCommon_Build,7
};
ButtonInfo g_ButtonInfo_TAdvance_Build = {
    "StarResource/Resource/UI/Icon/Terran/Common/AdvanceBuild1.png",
    "StarResource/Resource/UI/Icon/Terran/Common/AdvanceBuild2.png",
    "", ButtonType::TAdvance_Build,8
};
ButtonInfo g_ButtonInfo_TLift = {
    "StarResource/Resource/UI/Icon/Terran/Common/Lift1.png",
    "StarResource/Resource/UI/Icon/Terran/Common/Lift2.png",
    "", ButtonType::TLift,9
};
ButtonInfo g_ButtonInfo_TLand = {
    "StarResource/Resource/UI/Icon/Terran/Common/Land1.png",
    "StarResource/Resource/UI/Icon/Terran/Common/Land2.png",
    "", ButtonType::TLand,9
};

//Skill Icon
ButtonInfo g_ButtonInfo_TEMP = {
    "StarResource/Resource/UI/Icon/Terran/Skill/EMP1.png",
    "StarResource/Resource/UI/Icon/Terran/Skill/EMP2.png",
    "", ButtonType::TEMP,1
};
ButtonInfo g_ButtonInfo_TGhost_MP = {
    "StarResource/Resource/UI/Icon/Terran/Skill/Ghost_MP1.png",
    "StarResource/Resource/UI/Icon/Terran/Skill/Ghost_MP2.png",
    "", ButtonType::TGhost_MP,9
};
ButtonInfo g_ButtonInfo_TGhost_Sight = {
    "StarResource/Resource/UI/Icon/Terran/Skill/Ghost_Sight1.png",
    "StarResource/Resource/UI/Icon/Terran/Skill/Ghost_Sight2.png",
    "", ButtonType::TGhost_Sight,9
};
ButtonInfo g_ButtonInfo_TGoliath_Range = {
    "StarResource/Resource/UI/Icon/Terran/Skill/Goliath_Range1.png",
    "StarResource/Resource/UI/Icon/Terran/Skill/Goliath_Range2.png",
    "", ButtonType::TGoliath_Range,4
};
ButtonInfo g_ButtonInfo_TDefenciveMatrix = {
    "StarResource/Resource/UI/Icon/Terran/Skill/DefenciveMatrix1.png",
    "StarResource/Resource/UI/Icon/Terran/Skill/DefenciveMatrix2.png",
    "", ButtonType::TDefenciveMatrix,9
};
ButtonInfo g_ButtonInfo_TLockDown        = {
    "StarResource/Resource/UI/Icon/Terran/Skill/LockDown1.png",
    "StarResource/Resource/UI/Icon/Terran/Skill/LockDown2.png",
    "", ButtonType::TLockDown,9
};
ButtonInfo g_ButtonInfo_TWraith_MP = {
    "StarResource/Resource/UI/Icon/Terran/Skill/Wraith_MP1.png",
    "StarResource/Resource/UI/Icon/Terran/Skill/Wraith_MP2.png",
    "", ButtonType::TWraith_MP,9
};
ButtonInfo g_ButtonInfo_TRestoration = {
    "StarResource/Resource/UI/Icon/Terran/Skill/Restoration1.png",
    "StarResource/Resource/UI/Icon/Terran/Skill/Restoration2.png",
    "", ButtonType::TRestoration,4
};
ButtonInfo g_ButtonInfo_TMarine_Range = {
    "StarResource/Resource/UI/Icon/Terran/Skill/Marine_Range1.png",
    "StarResource/Resource/UI/Icon/Terran/Skill/Marine_Range2.png",
    "", ButtonType::TMarine_Range,1
};
ButtonInfo g_ButtonInfo_TMedic_MP     = {
    "StarResource/Resource/UI/Icon/Terran/Skill/Medic_MP1.png",
    "StarResource/Resource/UI/Icon/Terran/Skill/Medic_MP2.png",
    "", ButtonType::TMedic_MP,6
};
ButtonInfo g_ButtonInfo_TMedic_Heal     = {
    "StarResource/Resource/UI/Icon/Terran/Skill/Medic_Heal1.png",
    "StarResource/Resource/UI/Icon/Terran/Skill/Medic_Heal2.png",
    "", ButtonType::TMedic_Heal,9
};
ButtonInfo g_ButtonInfo_TMechanic_Aerial_AT = {
    "StarResource/Resource/UI/Icon/Terran/Skill/Mechanic_Aerial_AT1.png",
    "StarResource/Resource/UI/Icon/Terran/Skill/Mechanic_Aerial_AT2.png",
    "", ButtonType::TMechanic_Aerial_AT,4
};
ButtonInfo g_ButtonInfo_TMechanic_Aerial_DF = {
    "StarResource/Resource/UI/Icon/Terran/Skill/Mechanic_Aerial_DF1.png",
    "StarResource/Resource/UI/Icon/Terran/Skill/Mechanic_Aerial_DF2.png",
    "", ButtonType::TMechanic_Aerial_DF,5
};
ButtonInfo g_ButtonInfo_TMechanic_Ground_AT = {
    "StarResource/Resource/UI/Icon/Terran/Skill/Mechanic_Ground_AT1.png",
    "StarResource/Resource/UI/Icon/Terran/Skill/Mechanic_Ground_AT2.png",
    "", ButtonType::TMechanic_Ground_AT,1
};
ButtonInfo g_ButtonInfo_TMechanic_Ground_DF = {
    "StarResource/Resource/UI/Icon/Terran/Skill/Mechanic_Ground_DF1.png",
    "StarResource/Resource/UI/Icon/Terran/Skill/Mechanic_Ground_DF2.png",
    "", ButtonType::TMechanic_Ground_DF,2
};
ButtonInfo g_ButtonInfo_TBionic_AT = {
    "StarResource/Resource/UI/Icon/Terran/Skill/Bionic_AT1.png",
    "StarResource/Resource/UI/Icon/Terran/Skill/Bionic_AT2.png",
    "", ButtonType::TBionic_AT,1
};
ButtonInfo g_ButtonInfo_TBionic_DF = {
    "StarResource/Resource/UI/Icon/Terran/Skill/Bionic_DF1.png",
    "StarResource/Resource/UI/Icon/Terran/Skill/Bionic_DF2.png",
    "", ButtonType::TBionic_DF,2
};
ButtonInfo g_ButtonInfo_TBattle_MP = {
    "StarResource/Resource/UI/Icon/Terran/Skill/Battle_MP1.png",
    "StarResource/Resource/UI/Icon/Terran/Skill/Battle_MP2.png",
    "", ButtonType::TBattle_MP,9
};
ButtonInfo g_ButtonInfo_TVessel_MP = {
    "StarResource/Resource/UI/Icon/Terran/Skill/Vessel_MP1.png",
    "StarResource/Resource/UI/Icon/Terran/Skill/Vessel_MP2.png",
    "", ButtonType::TVessel_MP,3
};
ButtonInfo g_ButtonInfo_TVulture_Speed = {
    "StarResource/Resource/UI/Icon/Terran/Skill/Vulture_Speed1.png",
    "StarResource/Resource/UI/Icon/Terran/Skill/Vulture_Speed2.png",
    "", ButtonType::TVulture_Speed,1
};
ButtonInfo g_ButtonInfo_TScan          = {
    "StarResource/Resource/UI/Icon/Terran/Skill/Scan1.png",
    "StarResource/Resource/UI/Icon/Terran/Skill/Scan2.png",
    "", ButtonType::TScan,1
};
ButtonInfo g_ButtonInfo_TStimPack      = {
    "StarResource/Resource/UI/Icon/Terran/Skill/StimPack1.png",
    "StarResource/Resource/UI/Icon/Terran/Skill/StimPack2.png",
    "", ButtonType::TStimPack,7
};
ButtonInfo g_ButtonInfo_TYamato        = {
    "StarResource/Resource/UI/Icon/Terran/Skill/Yamato1.png",
    "StarResource/Resource/UI/Icon/Terran/Skill/Yamato2.png",
    "", ButtonType::TYamato,9
};
ButtonInfo g_ButtonInfo_TOptical_Flare = {
    "StarResource/Resource/UI/Icon/Terran/Skill/Optical_Flare1.png",
    "StarResource/Resource/UI/Icon/Terran/Skill/Optical_Flare2.png",
    "", ButtonType::TOptical_Flare,5
};
ButtonInfo g_ButtonInfo_TCloakingON    = {
    "StarResource/Resource/UI/Icon/Terran/Skill/CloakingON1.png",
    "StarResource/Resource/UI/Icon/Terran/Skill/CloakingON2.png",
    "", ButtonType::TCloakingON,9
};
ButtonInfo g_ButtonInfo_TCloakingOFF   = {
    "StarResource/Resource/UI/Icon/Terran/Skill/CloakingOFF1.png",
    "StarResource/Resource/UI/Icon/Terran/Skill/CloakingOFF2.png",
    "", ButtonType::TCloakingOFF,9
};
ButtonInfo g_ButtonInfo_TIrradiate     = {
    "StarResource/Resource/UI/Icon/Terran/Skill/Irradiate1.png",
    "StarResource/Resource/UI/Icon/Terran/Skill/Irradiate2.png",
    "", ButtonType::TIrradiate,2
};
ButtonInfo g_ButtonInfo_TNuclear       = {
    "StarResource/Resource/UI/Icon/Terran/Skill/Nuclear1.png",
    "StarResource/Resource/UI/Icon/Terran/Skill/Nuclear2.png",
    "", ButtonType::TNuclear,9
};

//Build Icon
ButtonInfo g_ButtonInfo_TNuclear_Silo       = {
    "StarResource/Resource/UI/Icon/Terran/Build/Nuclear_Silo1.png",
    "StarResource/Resource/UI/Icon/Terran/Build/Nuclear_Silo2.png",
    "", ButtonType::TNuclear_Silo,8
};
ButtonInfo g_ButtonInfo_TAcademy      = {
    "StarResource/Resource/UI/Icon/Terran/Build/Academy1.png",
    "StarResource/Resource/UI/Icon/Terran/Build/Academy2.png",
    "", ButtonType::TAcademy,7
};
ButtonInfo g_ButtonInfo_TArmory = {
    "StarResource/Resource/UI/Icon/Terran/Build/Armory1.png",
    "StarResource/Resource/UI/Icon/Terran/Build/Armory2.png",
    "", ButtonType::TArmory,4
};
ButtonInfo g_ButtonInfo_TBarracks           = {
    "StarResource/Resource/UI/Icon/Terran/Build/Barracks1.png",
    "StarResource/Resource/UI/Icon/Terran/Build/Barracks2.png",
    "", ButtonType::TBarracks,4
};
ButtonInfo g_ButtonInfo_TBunker       = {
    "StarResource/Resource/UI/Icon/Terran/Build/Bunker1.png",
    "StarResource/Resource/UI/Icon/Terran/Build/Bunker2.png",
    "", ButtonType::TNuclear_Silo,8
};
ButtonInfo g_ButtonInfo_TCommand_Center     = {
    "StarResource/Resource/UI/Icon/Terran/Build/Command_Center1.png",
    "StarResource/Resource/UI/Icon/Terran/Build/Command_Center2.png",
    "", ButtonType::TCommand_Center,1
};
ButtonInfo g_ButtonInfo_TComsat_Station     = {
    "StarResource/Resource/UI/Icon/Terran/Build/Comsat_Station1.png",
    "StarResource/Resource/UI/Icon/Terran/Build/Comsat_Station2.png",
    "", ButtonType::TComsat_Station,7
};
ButtonInfo g_ButtonInfo_TControl_Tower      = {
    "StarResource/Resource/UI/Icon/Terran/Build/Control_Tower1.png",
    "StarResource/Resource/UI/Icon/Terran/Build/Control_Tower2.png",
    "", ButtonType::TControl_Tower,7
};
ButtonInfo g_ButtonInfo_TCovert_Ops         = {
    "StarResource/Resource/UI/Icon/Terran/Build/Covert_Ops1.png",
    "StarResource/Resource/UI/Icon/Terran/Build/Covert_Ops2.png",
    "", ButtonType::TCovert_Ops,7
};
ButtonInfo g_ButtonInfo_TEngineering_Bay    = {
    "StarResource/Resource/UI/Icon/Terran/Build/Engineering_Bay1.png",
    "StarResource/Resource/UI/Icon/Terran/Build/Engineering_Bay2.png",
    "", ButtonType::TEngineering_Bay,5
};
ButtonInfo g_ButtonInfo_TFactory            = {
    "StarResource/Resource/UI/Icon/Terran/Build/Factory1.png",
    "StarResource/Resource/UI/Icon/Terran/Build/Factory2.png",
    "", ButtonType::TFactory,1
};
ButtonInfo g_ButtonInfo_TMachine_Shop       = {
    "StarResource/Resource/UI/Icon/Terran/Build/Machine_Shop1.png",
    "StarResource/Resource/UI/Icon/Terran/Build/Machine_Shop2.png",
    "", ButtonType::TMachine_Shop,9
};
ButtonInfo g_ButtonInfo_TMissile_Turret     = {
    "StarResource/Resource/UI/Icon/Terran/Build/Missile_Turret1.png",
    "StarResource/Resource/UI/Icon/Terran/Build/Missile_Turret2.png",
    "", ButtonType::TMissile_Turret,6
};
ButtonInfo g_ButtonInfo_TPhysics_Lab        = {
    "StarResource/Resource/UI/Icon/Terran/Build/Physics_Lab1.png",
    "StarResource/Resource/UI/Icon/Terran/Build/Physics_Lab2.png",
    "", ButtonType::TPhysics_Lab,8
};
ButtonInfo g_ButtonInfo_TRefinery           = {
    "StarResource/Resource/UI/Icon/Terran/Build/Refinery1.png",
    "StarResource/Resource/UI/Icon/Terran/Build/Refinery2.png",
    "", ButtonType::TRefinery,3
};
ButtonInfo g_ButtonInfo_TScience_Facility   = {
    "StarResource/Resource/UI/Icon/Terran/Build/Science_Facility1.png",
    "StarResource/Resource/UI/Icon/Terran/Build/Science_Facility2.png",
    "", ButtonType::TScience_Facility,3
};
ButtonInfo g_ButtonInfo_TStarPort         = {
    "StarResource/Resource/UI/Icon/Terran/Build/StarPort1.png",
    "StarResource/Resource/UI/Icon/Terran/Build/StarPort2.png",
    "", ButtonType::TStarPort,2
};
ButtonInfo g_ButtonInfo_TSupply_Depot = {
    "StarResource/Resource/UI/Icon/Terran/Build/Supply_Depot1.png",
    "StarResource/Resource/UI/Icon/Terran/Build/Supply_Depot2.png",
    "", ButtonType::TSupply_Depot,2
};

//Unit Icon
ButtonInfo g_ButtonInfo_TSCV          = {
    "StarResource/Resource/UI/Icon/Terran/Unit/SCV1.png",
    "StarResource/Resource/UI/Icon/Terran/Unit/SCV2.png",
    "", ButtonType::TSCV,1
};
ButtonInfo g_ButtonInfo_TBattle       = {
    "StarResource/Resource/UI/Icon/Terran/Unit/Battle1.png",
    "StarResource/Resource/UI/Icon/Terran/Unit/Battle2.png",
    "", ButtonType::TBattle,9
};
ButtonInfo g_ButtonInfo_TDropShip        = {
    "StarResource/Resource/UI/Icon/Terran/Unit/DropShip1.png",
    "StarResource/Resource/UI/Icon/Terran/Unit/DropShip2.png",
    "", ButtonType::TDropShip,9
};
ButtonInfo g_ButtonInfo_TFireBat          = {
    "StarResource/Resource/UI/Icon/Terran/Unit/FireBat1.png",
    "StarResource/Resource/UI/Icon/Terran/Unit/FireBat2.png",
    "", ButtonType::TFireBat,2
};
ButtonInfo g_ButtonInfo_TGhost         = {
    "StarResource/Resource/UI/Icon/Terran/Unit/Ghost1.png",
    "StarResource/Resource/UI/Icon/Terran/Unit/Ghost2.png",
    "", ButtonType::TGhost,3
};
ButtonInfo g_ButtonInfo_TGoliath          = {
    "StarResource/Resource/UI/Icon/Terran/Unit/Goliath1.png",
    "StarResource/Resource/UI/Icon/Terran/Unit/Goliath2.png",
    "", ButtonType::TGoliath,9
};
ButtonInfo g_ButtonInfo_TMarine          = {
    "StarResource/Resource/UI/Icon/Terran/Unit/Marine1.png",
    "StarResource/Resource/UI/Icon/Terran/Unit/Marine2.png",
    "", ButtonType::TMarine,1
};
ButtonInfo g_ButtonInfo_TMedic          = {
    "StarResource/Resource/UI/Icon/Terran/Unit/Medic1.png",
    "StarResource/Resource/UI/Icon/Terran/Unit/Medic2.png",
    "", ButtonType::TMedic,4
};
ButtonInfo g_ButtonInfo_TMine          = {
    "StarResource/Resource/UI/Icon/Terran/Unit/Mine1.png",
    "StarResource/Resource/UI/Icon/Terran/Unit/Mine2.png",
    "", ButtonType::TMine,9
};
ButtonInfo g_ButtonInfo_TSiege_Tank          = {
    "StarResource/Resource/UI/Icon/Terran/Unit/Siege_Tank1.png",
    "StarResource/Resource/UI/Icon/Terran/Unit/Siege_Tank2.png",
    "", ButtonType::TSiege_Tank,9
};
ButtonInfo g_ButtonInfo_TTank          = {
    "StarResource/Resource/UI/Icon/Terran/Unit/Tank1.png",
    "StarResource/Resource/UI/Icon/Terran/Unit/Tank2.png",
    "", ButtonType::TTank,9
};
ButtonInfo g_ButtonInfo_TValkyrie            = {
    "StarResource/Resource/UI/Icon/Terran/Unit/Valkyrie1.png",
    "StarResource/Resource/UI/Icon/Terran/Unit/Valkyrie2.png",
    "", ButtonType::TValkyrie,9
};
ButtonInfo g_ButtonInfo_TVessel             = {
    "StarResource/Resource/UI/Icon/Terran/Unit/Vessel1.png",
    "StarResource/Resource/UI/Icon/Terran/Unit/Vessel2.png",
    "", ButtonType::TVessel,9
};
ButtonInfo g_ButtonInfo_TVulture = {
    "StarResource/Resource/UI/Icon/Terran/Unit/Vulture1.png",
    "StarResource/Resource/UI/Icon/Terran/Unit/Vulture2.png",
    "", ButtonType::TVulture,9
};
ButtonInfo g_ButtonInfo_TWraith = {
    "StarResource/Resource/UI/Icon/Terran/Unit/Wraith1.png",
    "StarResource/Resource/UI/Icon/Terran/Unit/Wraith2.png",
    "", ButtonType::TWraith,9
};


ButtonInfo* FindButtonInfo(ButtonType type)
{
    switch (type)
    {
    case ButtonType::None:    return nullptr;
    case ButtonType::TAttack: return &g_ButtonInfo_TAttack;
    case ButtonType::TMove:   return &g_ButtonInfo_TMove;
    case ButtonType::TSetRellyPoint: return &g_ButtonInfo_TSetRellyPoint;
    case ButtonType::TUnLoad: return &g_ButtonInfo_TUnLoad;
    case ButtonType::TLoad:   return &g_ButtonInfo_TLoad;
    case ButtonType::TPatrol: return &g_ButtonInfo_TPatrol;
    case ButtonType::TReturn: return &g_ButtonInfo_TReturn;
    case ButtonType::THold:   return &g_ButtonInfo_THold;
    case ButtonType::TStop:   return &g_ButtonInfo_TStop;
    case ButtonType::TGather: return &g_ButtonInfo_TGather;
    case ButtonType::TCancel: return &g_ButtonInfo_TCancel;
    case ButtonType::TRepair: return &g_ButtonInfo_TRepair;
    case ButtonType::TCommon_Build:  return &g_ButtonInfo_TCommon_Build;
    case ButtonType::TAdvance_Build: return &g_ButtonInfo_TAdvance_Build;
    case ButtonType::TLift:   return &g_ButtonInfo_TLand;
    case ButtonType::TLand:   return &g_ButtonInfo_TLand;
    case ButtonType::TEMP:    return &g_ButtonInfo_TEMP;
    case ButtonType::TGhost_MP:      return &g_ButtonInfo_TGhost_MP;
    case ButtonType::TGhost_Sight:   return &g_ButtonInfo_TGhost_Sight;
    case ButtonType::TGoliath_Range: return &g_ButtonInfo_TGoliath_Range;
    case ButtonType::TDefenciveMatrix:   return &g_ButtonInfo_TDefenciveMatrix;
    case ButtonType::TLockDown:      return &g_ButtonInfo_TLockDown;
    case ButtonType::TWraith_MP:     return &g_ButtonInfo_TWraith_MP;
    case ButtonType::TRestoration:   return &g_ButtonInfo_TRestoration;
    case ButtonType::TMarine_Range:  return &g_ButtonInfo_TMarine_Range;
    case ButtonType::TMedic_MP:      return &g_ButtonInfo_TMedic_MP;
    case ButtonType::TMedic_Heal:    return &g_ButtonInfo_TMedic_Heal;
    case ButtonType::TMechanic_Aerial_AT: return &g_ButtonInfo_TMechanic_Aerial_AT;
    case ButtonType::TMechanic_Aerial_DF: return &g_ButtonInfo_TMechanic_Aerial_DF;
    case ButtonType::TMechanic_Ground_AT: return &g_ButtonInfo_TMechanic_Ground_AT;
    case ButtonType::TMechanic_Ground_DF: return &g_ButtonInfo_TMechanic_Ground_DF;
    case ButtonType::TBionic_AT:     return &g_ButtonInfo_TBionic_AT;    
    case ButtonType::TBionic_DF:     return &g_ButtonInfo_TBionic_DF;
    case ButtonType::TVessel_MP:     return &g_ButtonInfo_TVessel_MP;    
    case ButtonType::TBattle_MP:     return &g_ButtonInfo_TBattle_MP;    
    case ButtonType::TVulture_Speed: return &g_ButtonInfo_TVulture_Speed;
    case ButtonType::TScan:          return &g_ButtonInfo_TScan;         
    case ButtonType::TStimPack:      return &g_ButtonInfo_TStimPack;    
    case ButtonType::TYamato:        return &g_ButtonInfo_TYamato;       
    case ButtonType::TOptical_Flare: return &g_ButtonInfo_TOptical_Flare;
    case ButtonType::TCloakingON:    return &g_ButtonInfo_TCloakingON;   
    case ButtonType::TCloakingOFF:   return &g_ButtonInfo_TCloakingOFF;  
    case ButtonType::TIrradiate:     return &g_ButtonInfo_TIrradiate;    
    case ButtonType::TNuclear:       return &g_ButtonInfo_TNuclear;     
    case ButtonType::TNuclear_Silo:     return &g_ButtonInfo_TNuclear_Silo;
    case ButtonType::TAcademy:          return &g_ButtonInfo_TAcademy;
    case ButtonType::TArmory:           return &g_ButtonInfo_TArmory;
    case ButtonType::TBarracks:         return &g_ButtonInfo_TBarracks;
    case ButtonType::TBunker:           return &g_ButtonInfo_TBunker;
    case ButtonType::TCommand_Center:   return &g_ButtonInfo_TCommand_Center;
    case ButtonType::TComsat_Station:   return &g_ButtonInfo_TComsat_Station;
    case ButtonType::TControl_Tower:    return &g_ButtonInfo_TControl_Tower;
    case ButtonType::TCovert_Ops:       return &g_ButtonInfo_TCovert_Ops;
    case ButtonType::TEngineering_Bay:  return &g_ButtonInfo_TEngineering_Bay;
    case ButtonType::TFactory:          return &g_ButtonInfo_TFactory;
    case ButtonType::TMachine_Shop:     return &g_ButtonInfo_TMachine_Shop;
    case ButtonType::TMissile_Turret:   return &g_ButtonInfo_TMissile_Turret;
    case ButtonType::TPhysics_Lab:      return &g_ButtonInfo_TPhysics_Lab;
    case ButtonType::TRefinery:         return &g_ButtonInfo_TRefinery;
    case ButtonType::TScience_Facility: return &g_ButtonInfo_TScience_Facility;
    case ButtonType::TStarPort:         return &g_ButtonInfo_TStarPort;
    case ButtonType::TSupply_Depot:     return &g_ButtonInfo_TSupply_Depot;
    case ButtonType::TSCV:              return &g_ButtonInfo_TSCV;
    case ButtonType::TBattle:           return &g_ButtonInfo_TBattle;
    case ButtonType::TDropShip:         return &g_ButtonInfo_TDropShip;
    case ButtonType::TFireBat:          return &g_ButtonInfo_TFireBat;
    case ButtonType::TGhost:            return &g_ButtonInfo_TGhost;
    case ButtonType::TGoliath:          return &g_ButtonInfo_TGoliath;
    case ButtonType::TMarine:           return &g_ButtonInfo_TMarine;
    case ButtonType::TMedic:            return &g_ButtonInfo_TMedic;
    case ButtonType::TMine:             return &g_ButtonInfo_TMine;
    case ButtonType::TSiege_Tank:       return &g_ButtonInfo_TSiege_Tank;
    case ButtonType::TTank:             return &g_ButtonInfo_TTank;
    case ButtonType::TValkyrie:         return &g_ButtonInfo_TValkyrie;
    case ButtonType::TVessel:           return &g_ButtonInfo_TVessel;
    case ButtonType::TVulture:          return &g_ButtonInfo_TVulture;
    case ButtonType::TWraith:           return &g_ButtonInfo_TWraith;
    default:  break;
    }
    return &g_ButtonInfo_TMine;
}

int FindButtonPos(ButtonType type)
{
    switch (type)
    {
    case ButtonType::None:    break;
    case ButtonType::TAttack: return g_ButtonInfo_TAttack.iconPos;
    case ButtonType::TMove:   return g_ButtonInfo_TMove.iconPos;
    case ButtonType::TSetRellyPoint: return g_ButtonInfo_TSetRellyPoint.iconPos;
    case ButtonType::TUnLoad: return g_ButtonInfo_TUnLoad.iconPos;
    case ButtonType::TLoad:   return g_ButtonInfo_TLoad.iconPos;
    case ButtonType::TPatrol: return g_ButtonInfo_TPatrol.iconPos;
    case ButtonType::TReturn: return g_ButtonInfo_TReturn.iconPos;
    case ButtonType::THold:   return g_ButtonInfo_THold.iconPos;
    case ButtonType::TStop:   return g_ButtonInfo_TStop.iconPos;
    case ButtonType::TGather: return g_ButtonInfo_TGather.iconPos;
    case ButtonType::TCancel: return g_ButtonInfo_TCancel.iconPos;
    case ButtonType::TRepair: return g_ButtonInfo_TRepair.iconPos;
    case ButtonType::TCommon_Build:  return g_ButtonInfo_TCommon_Build.iconPos;
    case ButtonType::TAdvance_Build: return g_ButtonInfo_TAdvance_Build.iconPos;
    case ButtonType::TLift:   return g_ButtonInfo_TLand.iconPos;
    case ButtonType::TLand:   return g_ButtonInfo_TLand.iconPos;
    case ButtonType::TEMP:    return g_ButtonInfo_TEMP.iconPos;
    case ButtonType::TGhost_MP:      return g_ButtonInfo_TGhost_MP.iconPos;
    case ButtonType::TGhost_Sight:   return g_ButtonInfo_TGhost_Sight.iconPos;
    case ButtonType::TGoliath_Range: return g_ButtonInfo_TGoliath_Range.iconPos;
    case ButtonType::TDefenciveMatrix:   return g_ButtonInfo_TDefenciveMatrix.iconPos;
    case ButtonType::TLockDown:      return g_ButtonInfo_TLockDown.iconPos;
    case ButtonType::TWraith_MP:     return g_ButtonInfo_TWraith_MP.iconPos;
    case ButtonType::TRestoration:   return g_ButtonInfo_TRestoration.iconPos;
    case ButtonType::TMarine_Range:  return g_ButtonInfo_TMarine_Range.iconPos;
    case ButtonType::TMedic_MP:      return g_ButtonInfo_TMedic_MP.iconPos;
    case ButtonType::TMedic_Heal:    return g_ButtonInfo_TMedic_Heal.iconPos;
    case ButtonType::TMechanic_Aerial_AT: return g_ButtonInfo_TMechanic_Aerial_AT.iconPos;
    case ButtonType::TMechanic_Aerial_DF: return g_ButtonInfo_TMechanic_Aerial_DF.iconPos;
    case ButtonType::TMechanic_Ground_AT: return g_ButtonInfo_TMechanic_Ground_AT.iconPos;
    case ButtonType::TMechanic_Ground_DF: return g_ButtonInfo_TMechanic_Ground_DF.iconPos;
    case ButtonType::TBionic_AT:     return g_ButtonInfo_TBionic_AT.iconPos;    
    case ButtonType::TBionic_DF:     return g_ButtonInfo_TBionic_DF.iconPos;
    case ButtonType::TVessel_MP:     return g_ButtonInfo_TVessel_MP.iconPos;    
    case ButtonType::TBattle_MP:     return g_ButtonInfo_TBattle_MP.iconPos;    
    case ButtonType::TVulture_Speed: return g_ButtonInfo_TVulture_Speed.iconPos;
    case ButtonType::TScan:          return g_ButtonInfo_TScan.iconPos;         
    case ButtonType::TStimPack:      return g_ButtonInfo_TStimPack.iconPos;    
    case ButtonType::TYamato:        return g_ButtonInfo_TYamato.iconPos;       
    case ButtonType::TOptical_Flare: return g_ButtonInfo_TOptical_Flare.iconPos;
    case ButtonType::TCloakingON:    return g_ButtonInfo_TCloakingON.iconPos;   
    case ButtonType::TCloakingOFF:   return g_ButtonInfo_TCloakingOFF.iconPos;  
    case ButtonType::TIrradiate:     return g_ButtonInfo_TIrradiate.iconPos;    
    case ButtonType::TNuclear:       return g_ButtonInfo_TNuclear.iconPos;     
    case ButtonType::TNuclear_Silo:     return g_ButtonInfo_TNuclear_Silo.iconPos;
    case ButtonType::TAcademy:          return g_ButtonInfo_TAcademy.iconPos;
    case ButtonType::TArmory:           return g_ButtonInfo_TArmory.iconPos;
    case ButtonType::TBarracks:         return g_ButtonInfo_TBarracks.iconPos;
    case ButtonType::TBunker:           return g_ButtonInfo_TBunker.iconPos;
    case ButtonType::TCommand_Center:   return g_ButtonInfo_TCommand_Center.iconPos;
    case ButtonType::TComsat_Station:   return g_ButtonInfo_TComsat_Station.iconPos;
    case ButtonType::TControl_Tower:    return g_ButtonInfo_TControl_Tower.iconPos;
    case ButtonType::TCovert_Ops:       return g_ButtonInfo_TCovert_Ops.iconPos;
    case ButtonType::TEngineering_Bay:  return g_ButtonInfo_TEngineering_Bay.iconPos;
    case ButtonType::TFactory:          return g_ButtonInfo_TFactory.iconPos;
    case ButtonType::TMachine_Shop:     return g_ButtonInfo_TMachine_Shop.iconPos;
    case ButtonType::TMissile_Turret:   return g_ButtonInfo_TMissile_Turret.iconPos;
    case ButtonType::TPhysics_Lab:      return g_ButtonInfo_TPhysics_Lab.iconPos;
    case ButtonType::TRefinery:         return g_ButtonInfo_TRefinery.iconPos;
    case ButtonType::TScience_Facility: return g_ButtonInfo_TScience_Facility.iconPos;
    case ButtonType::TStarPort:         return g_ButtonInfo_TStarPort.iconPos;
    case ButtonType::TSupply_Depot:     return g_ButtonInfo_TSupply_Depot.iconPos;
    case ButtonType::TSCV:              return g_ButtonInfo_TSCV.iconPos;
    case ButtonType::TBattle:           return g_ButtonInfo_TBattle.iconPos;
    case ButtonType::TDropShip:         return g_ButtonInfo_TDropShip.iconPos;
    case ButtonType::TFireBat:          return g_ButtonInfo_TFireBat.iconPos;
    case ButtonType::TGhost:            return g_ButtonInfo_TGhost.iconPos;
    case ButtonType::TGoliath:          return g_ButtonInfo_TGoliath.iconPos;
    case ButtonType::TMarine:           return g_ButtonInfo_TMarine.iconPos;
    case ButtonType::TMedic:            return g_ButtonInfo_TMedic.iconPos;
    case ButtonType::TMine:             return g_ButtonInfo_TMine.iconPos;
    case ButtonType::TSiege_Tank:       return g_ButtonInfo_TSiege_Tank.iconPos;
    case ButtonType::TTank:             return g_ButtonInfo_TTank.iconPos;
    case ButtonType::TValkyrie:         return g_ButtonInfo_TValkyrie.iconPos;
    case ButtonType::TVessel:           return g_ButtonInfo_TVessel.iconPos;
    case ButtonType::TVulture:          return g_ButtonInfo_TVulture.iconPos;
    case ButtonType::TWraith:           return g_ButtonInfo_TWraith.iconPos;
    default:  break;
    }
    return 0;
}

UnitControlButton g_UnitControlButton_TSCV = {
    ActorType::SCV,
    {ButtonType::TMove, ButtonType::TStop, ButtonType::TAttack,
    ButtonType::TRepair, ButtonType::TGather, ButtonType::None,
    ButtonType::TCommon_Build,ButtonType::TAdvance_Build,ButtonType::None}
};

UnitControlButton g_UnitControlButton_TMarine = {
    ActorType::Marine,
    {ButtonType::TMove, ButtonType::TStop, ButtonType::TAttack,
    ButtonType::TPatrol, ButtonType::THold, ButtonType::None,
    ButtonType::TStimPack,ButtonType::None,ButtonType::None}
};

UnitControlButton g_UnitControlButton_TCommandCenter = {
    ActorType::CommandCenter,
    {ButtonType::TSCV,ButtonType::None,ButtonType::None,
    ButtonType::None,ButtonType::None,ButtonType::TSetRellyPoint,
    ButtonType::TComsat_Station,ButtonType::TNuclear_Silo,
    ButtonType::TLift}
};

UnitControlButton g_UnitControlButton_TBarrack = {
    ActorType::Barrack,
    {ButtonType::TMarine,ButtonType::TFireBat,ButtonType::TGhost,
    ButtonType::TMedic,ButtonType::None,ButtonType::TSetRellyPoint,
    ButtonType::None,ButtonType::None, ButtonType::TLift}
};

UnitControlButton g_UnitControlButton_TEngineeringBay = {
    ActorType::EngineeringBay,
    {ButtonType::TBionic_AT,ButtonType::TBionic_DF,ButtonType::None,
    ButtonType::None,ButtonType::None,ButtonType::None,
    ButtonType::None,ButtonType::None,  ButtonType::TLift}
};

UnitControlButton g_UnitControlButton_TAcademy = {
    ActorType::Academy,
    {ButtonType::TMarine_Range, ButtonType::TStimPack, ButtonType::None,
    ButtonType::TRestoration, ButtonType::TOptical_Flare, ButtonType::TMedic_MP,
    ButtonType::None, ButtonType::None, ButtonType::None}
};

UnitControlButton g_UnitControlButton_TFactory = {
    ActorType::Factory,
    {ButtonType::TVulture, ButtonType::TTank, ButtonType::TGoliath,
    ButtonType::None, ButtonType::None, ButtonType::TSetRellyPoint,
    ButtonType::TMachine_Shop, ButtonType::None, ButtonType::TLift}
};

UnitControlButton g_UnitControlButton_TScienceFacility = {
    ActorType::ScienceFacility,
    {ButtonType::TEMP, ButtonType::TIrradiate, ButtonType::TVessel_MP,
    ButtonType::None, ButtonType::None, ButtonType::None,
    ButtonType::TCovert_Ops, ButtonType::TPhysics_Lab, ButtonType::TLift}
};

UnitControlButton g_UnitControlButton_TArmory = {
    ActorType::Armory,
    {ButtonType::TBionic_AT, ButtonType::TBionic_DF, ButtonType::None,
    ButtonType::None, ButtonType::None, ButtonType::None,
    ButtonType::None, ButtonType::None, ButtonType::TLift}
};

UnitControlButton g_UnitControlButton_TBunker = {
    ActorType::Bunker,
    {ButtonType::TWraith, ButtonType::TDropShip, ButtonType::TVessel,
    ButtonType::TBattle, ButtonType::TValkyrie, ButtonType::TSetRellyPoint,
    ButtonType::None, ButtonType::None, ButtonType::TLift}
};

UnitControlButton g_UnitControlButton_TStarPort = {
    ActorType::StarPort,
    {ButtonType::TBionic_AT, ButtonType::TBionic_DF, ButtonType::None,
    ButtonType::None, ButtonType::None, ButtonType::None,
    ButtonType::None, ButtonType::None, ButtonType::TLift}
};

UnitControlButton g_UnitControlButton_TRefinery = {
    ActorType::Refinery,
    {ButtonType::None, ButtonType::None, ButtonType::None,
    ButtonType::None, ButtonType::None, ButtonType::None,
     ButtonType::None, ButtonType::None, ButtonType::None }};

UnitControlButton g_UnitControlButton_TSupplyDepot = {
    ActorType::SupplyDepot,
    {ButtonType::None, ButtonType::TBionic_DF, ButtonType::None,
    ButtonType::None, ButtonType::None, ButtonType::None,
     ButtonType::None, ButtonType::None, ButtonType::None}};



UnitControlButton* FindUnitControlButton(Actor* actor)
{
    switch (actor->mActorType)
    {
    case ActorType::SCV:
    {
        switch (actor->mUnitComp->mCurAction)
        {
        case ActionState::Idle:
            return &g_UnitControlButton_TSCV;
        case ActionState::Building:
            return ReturnOnlyCancel(actor);
        }
    } break;
    case ActorType::Marine: return &g_UnitControlButton_TMarine;
    case ActorType::CommandCenter:
    {
        switch (actor->mUnitComp->mCurAction)
        {
        case ActionState::Idle:     return &g_UnitControlButton_TCommandCenter;
        case ActionState::Building: return ReturnOnlyCancel(actor);
        }
        return &g_UnitControlButton_TCommandCenter;
    }
    case ActorType::Barrack:
    {
        switch (actor->mUnitComp->mCurAction)
        {
        case ActionState::Idle:            return &g_UnitControlButton_TBarrack;
        case ActionState::Building:            return ReturnOnlyCancel(actor);
        }
        return &g_UnitControlButton_TBarrack;
    }
    break;
    case ActorType::EngineeringBay:
    {
        switch (actor->mUnitComp->mCurAction)
        {
        case ActionState::Idle:     return &g_UnitControlButton_TEngineeringBay;
        case ActionState::Building: return ReturnOnlyCancel(actor);
        }
        return &g_UnitControlButton_TBarrack;
    } break;
    case ActorType::Academy:
    {
        switch (actor->mUnitComp->mCurAction)
        {
        case ActionState::Idle:       return &g_UnitControlButton_TAcademy;
        case ActionState::Building:   return ReturnOnlyCancel(actor);
        }
    }
    case ActorType::Bunker:
    {
        switch (actor->mUnitComp->mCurAction)
        {
        case ActionState::Idle:            return &g_UnitControlButton_TBunker;
        case ActionState::Building:        return ReturnOnlyCancel(actor);
        }
    }
    case ActorType::StarPort:
    {
        switch (actor->mUnitComp->mCurAction)
        {
        case ActionState::Idle:     return &g_UnitControlButton_TStarPort;
        case ActionState::Building: return ReturnOnlyCancel(actor);
        }
    }
    case ActorType::Armory:
    {
        switch (actor->mUnitComp->mCurAction)
        {
        case ActionState::Idle:            return &g_UnitControlButton_TArmory;
        case ActionState::Building:        return ReturnOnlyCancel(actor);
        }
    }
    case ActorType::SupplyDepot:
    {
        switch (actor->mUnitComp->mCurAction)
        {
        case ActionState::Idle:            return &g_UnitControlButton_TSupplyDepot;
        case ActionState::Building:        return ReturnOnlyCancel(actor);
        }
    }
    case ActorType::Refinery:
    {
        switch (actor->mUnitComp->mCurAction)
        {
        case ActionState::Idle:            return &g_UnitControlButton_TRefinery;
        case ActionState::Building:            return ReturnOnlyCancel(actor);
        }
    }
    case ActorType::ScienceFacility:
    {
        switch (actor->mUnitComp->mCurAction)
        {
        case ActionState::Idle:            return &g_UnitControlButton_TScienceFacility;
        case ActionState::Building:        return ReturnOnlyCancel(actor);
        }
    }
    default:
        break;
    }
    return &g_UnitControlButton_TSCV;
}

UnitControlButton* ReturnOnlyCancel(Actor* actor)
{
    UnitControlButton cancelButton = {
        actor->mActorType,
        {ButtonType::None, ButtonType::None, ButtonType::None,
        ButtonType::None, ButtonType::None, ButtonType::None,
         ButtonType::None, ButtonType::None, ButtonType::TCancel}
    };
    return &cancelButton;
}
