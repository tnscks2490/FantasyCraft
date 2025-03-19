#include "pch.h"
#include "Weapon/Weapon.h"
#include "Actor.h"

void Weapon::CoolTime(float delta)
{
    if (IsUsing)
    {
        mTimer += delta;
        if (mTimer > mCoolTime)
        {
            mTimer  = 0.f;
            IsUsing   = false;
        }
    }
}
