#pragma once

#include "Weapon/Weapon.h"

class Weapon_Spell : public Weapon
{
public:

    Weapon_Spell(Actor* actor);
    virtual void update(float delta) override;
    virtual void Use() override;
};


