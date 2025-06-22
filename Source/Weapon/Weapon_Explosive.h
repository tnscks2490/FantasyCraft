#pragma once

#include "Weapon/Weapon.h"

class Weapon_Explosive : public Weapon
{
public:

    Weapon_Explosive(Actor* actor);
    virtual void update(float delta) override;
    virtual void Use(Actor* target) override;
};


