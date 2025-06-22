#pragma once

#include "Weapon/Weapon.h"

class Weapon_Concussive : public Weapon
{
public:

    Weapon_Concussive(Actor* actor);
    virtual void update(float delta) override;
    virtual void Use(Actor* target) override;
};


