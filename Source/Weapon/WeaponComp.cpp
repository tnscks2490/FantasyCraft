#include "pch.h"
#include "Actor.h"
#include "WeaponComp.h"
#include "Weapon/Weapon.h"
#include "Weapon/Weapon_Normal.h"
#include "Weapon/Weapon_Explosive.h"
#include "Weapon/Weapon_Concussive.h"
#include "Weapon/Weapon_Spell.h"


WeaponComp::WeaponComp(Actor* actor)
    : IActorComp(actor)
{
    actor->mWeaponComp = this;

    auto type = ClassifyWeapon(actor->mActorType);
    AddWeapon(type);
}

WeaponComp::~WeaponComp()
{
    if (mActor)
        mActor->mWeaponComp = nullptr;

}

void WeaponComp::MessageProc(ActorMessage& msg)
{

}

void WeaponComp::update(float delta)
{
    TakeAimAndShoot();
    if (mCurWeapon) mCurWeapon->update(delta);
}

void WeaponComp::SelectWeapon() {

}

void WeaponComp::TakeAimAndShoot() const {
}

void WeaponComp::AddWeapon(WeaponType type)
{
    Weapon* weapon = nullptr;

    switch (type)
    {
    case WeaponType::None:
        break;
    case WeaponType::Normal:
        weapon = new Weapon_Normal(mActor);
        break;
    case WeaponType::Explosive:
        weapon = new Weapon_Explosive(mActor);
        break;
    case WeaponType::Concussive:
        weapon = new Weapon_Concussive(mActor);
        break;
    case WeaponType::Spell:
        weapon = new Weapon_Spell(mActor);
        break;
    default:
        break;
    }

    mWeaponList.push_back(weapon);
    mCurWeapon = weapon;
}

void WeaponComp::DoAction()
{
    if (mCurWeapon)
        mCurWeapon->Use();
}

WeaponType WeaponComp::ClassifyWeapon(ActorType type)
{
    switch (type)
    {
    //case ActorType::Medic:       break;
    //case ActorType::Bunker:        break;
    case ActorType::SCV:       return WeaponType::Normal;
    case ActorType::Marine:    return WeaponType::Normal;
    case ActorType::FireBat:   return WeaponType ::Concussive;
    case ActorType::Ghost:     return WeaponType ::Concussive;
    case ActorType::Vulture:   return WeaponType ::Concussive;
    case ActorType::Tank:      return WeaponType ::Explosive;
    case ActorType::Goliath:   return WeaponType ::Normal;
    case ActorType::Wraith:    return WeaponType ::Normal;
    case ActorType::Valkyrie:  return WeaponType ::Explosive;
    }
    return WeaponType::Normal;
}




