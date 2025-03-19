#pragma once

#include "Weapon/Weapon.h"

class Weapon_Normal : public Weapon
{
public:

    Weapon_Normal(Actor* actor);
    virtual void update(float delta) override;
    virtual void Use() override;
};


