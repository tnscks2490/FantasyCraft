#pragma once
#include "PreDefines.h"

#define MAX_BUTTON 9 

enum class ButtonType
{
    None,
    //Common
    TAttack,
    TMove,
    TSetRellyPoint,
    TUnLoad,
    TLoad,
    TPatrol,
    TReturn,
    THold,
    TStop,
    TGather,
    TCancel,
    TRepair,
    TCommon_Build,
    TAdvance_Build,
    TLift,
    TLand,
    //Skill
    TEMP,
    TGhost_MP,
    TGhost_Sight,
    TGoliath_Range,
    TDefenciveMatrix,
    TLockDown,
    TWraith_MP,
    TRestoration,
    TMarine_Range,
    TMedic_MP,
    TMedic_Heal,
    TMechanic_Aerial_AT,
    TMechanic_Aerial_DF,
    TMechanic_Ground_AT,
    TMechanic_Ground_DF,
    TBionic_AT,
    TBionic_DF,
    TVessel_MP,
    TBattle_MP,
    TVulture_Speed,
    TScan,
    TStimPack,
    TYamato,
    TOptical_Flare,
    TCloakingON,
    TCloakingOFF,
    TIrradiate,
    TNuclear,
    //Build
    TNuclear_Silo,
    TAcademy,
    TArmory,
    TBarracks,
    TBunker,
    TCommand_Center,
    TComsat_Station,
    TControl_Tower,
    TCovert_Ops,
    TEngineering_Bay,
    TFactory,
    TMachine_Shop,
    TMissile_Turret,
    TPhysics_Lab,
    TRefinery,
    TScience_Facility,
    TStarPort,
    TSupply_Depot,
    //Unit
    TSCV,
    TBattle,
    TDropShip,
    TFireBat,
    TGhost,
    TGoliath,
    TMarine,
    TMedic,
    TMine,
    TSiege_Tank,
    TTank,
    TValkyrie,
    TVessel,
    TVulture,
    TWraith,
};


struct ButtonInfo
{
    std::string_view normal_Image;
    std::string_view selected_Image;
    std::string_view disable_Image;
    ButtonType type;
    int iconPos;


    void* data = nullptr;
};

ButtonInfo* FindButtonInfo(ButtonType type);
int FindButtonPos(ButtonType type);


struct UnitControlButton
{
    ActorType Atype;
    ButtonType buttons[MAX_BUTTON];

};

UnitControlButton* FindUnitControlButton(ActorType Atype);
