#include "UpgradeBluePrint.h"


UpgradeBluePrint g_error = {UpgradeType::None, 0, 0, 0};
UpgradeBluePrint g_BionicAT1 = {UpgradeType::BionicAT1, 100, 100, 112.f};
UpgradeBluePrint g_BionicAT2 = {UpgradeType::BionicAT2, 175, 175, 134.f};
UpgradeBluePrint g_BionicAT3 = {UpgradeType::BionicAT3, 250, 250, 157.f};

UpgradeBluePrint g_BionicDF1 = {UpgradeType::BionicAT1, 100, 100, 112.f};
UpgradeBluePrint g_BionicDF2 = {UpgradeType::BionicAT2, 175, 175, 134.f};
UpgradeBluePrint g_BionicDF3 = {UpgradeType::BionicAT3, 250, 250, 157.f};

















UpgradeBluePrint& FindUpgradeBP(UpgradeType type)
{
    switch (type)
    {
    case UpgradeType::None: return g_error;
    case UpgradeType::BionicAT1: return g_BionicAT1;
    case UpgradeType::BionicAT2: return g_BionicAT2;
    case UpgradeType::BionicAT3: return g_BionicAT3;
    case UpgradeType::BionicDF1: return g_BionicDF1;
    case UpgradeType::BionicDF2: return g_BionicDF2;
    case UpgradeType::BionicDF3: return g_BionicDF3;
    case UpgradeType::MechanicAT:
        break;
    case UpgradeType::MechanicDF:
        break;
    default:
        break;
    }
    return g_error;
}
