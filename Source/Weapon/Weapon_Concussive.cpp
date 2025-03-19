#include "pch.h"
#include "Actor.h"
#include "UnitComp.h"
#include "Weapon.h"
#include "Weapon_Concussive.h"

Weapon_Concussive::Weapon_Concussive(Actor* actor)
    : Weapon(actor)
{
    mType = WeaponType::Concussive;
}

void Weapon_Concussive::update(float delta)
{
    CoolTime(delta);
}

void Weapon_Concussive::Use()
{
    if (!IsUsing)
    {
        IsUsing  = true;
    }
}
