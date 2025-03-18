#include "pch.h"
#include "Weapon/Weapon.h"
#include "Actor.h"

void Weapon::CoolTime(float cooltime, float delta)
{
    if (IsUsing)
    {
        mCoolTime += delta;
        if (mCoolTime > cooltime)
        {
            mCoolTime = 0.f;
            IsUsing   = false;
        }
    }
}
