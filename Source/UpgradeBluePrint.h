#pragma once

#include "Actor.h"

enum class UpgradeType
{
    None,
    BionicAT1,
    BionicAT2,
    BionicAT3,
    BionicDF1,
    BionicDF2,
    BionicDF3,
    MechanicAT,
    MechanicDF,

};




struct UpgradeBluePrint
{
    UpgradeType type = UpgradeType::None;
    int mineralCost = 0;
    int gasCost     = 0;
    float buildTime   = 0.f;
};


UpgradeBluePrint& FindUpgradeBP(UpgradeType type);
