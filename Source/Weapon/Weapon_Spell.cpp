#include "pch.h"
#include "Actor.h"
#include "UnitComp.h"
#include "Weapon.h"
#include "Weapon_Spell.h"

Weapon_Spell::Weapon_Spell(Actor* actor)
    : Weapon(actor)
{
    mType = WeaponType::Spell;
}

void Weapon_Spell::update(float delta)
{
    CoolTime(delta);
}

void Weapon_Spell::Use(Actor* target)
{
    if (!IsUsing)
    {
        IsUsing  = true;
    }
}
