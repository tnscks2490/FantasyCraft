#include "pch.h"
#include "Actor.h"
#include "UnitComp.h"
#include "Weapon.h"
#include "Weapon_Explosive.h"

Weapon_Explosive::Weapon_Explosive(Actor* actor)
    : Weapon(actor)
{
    mType = WeaponType::Explosive;
}

void Weapon_Explosive::update(float delta)
{
    CoolTime(delta);
}

void Weapon_Explosive::Use(Actor* target)
{
    if (!IsUsing)
    {
        IsUsing  = true;
    }
}
