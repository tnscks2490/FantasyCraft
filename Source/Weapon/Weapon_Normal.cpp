#include "pch.h"
#include "Actor.h"
#include "UnitComp.h"
#include "Weapon.h"
#include "Weapon_Normal.h"

Weapon_Normal::Weapon_Normal(Actor* actor)
    : Weapon(actor)
{
    mType = WeaponType::Normal;
    SetAttackDelay(actor->mActorType);

}

void Weapon_Normal::update(float delta)
{
    CoolTime(delta);
}

void Weapon_Normal::Use()
{
    if (!IsUsing)
    {
        IsUsing  = true;
        mActor->mUnitComp->cmdLocked  = true;
        mActor->mUnitComp->mCurAction = ActionState::Attack;
    }
}
