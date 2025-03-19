#include "pch.h"
#include "Actor.h"
#include "WeaponComp.h"
#include "Weapon/Weapon.h"
#include "Weapon/Weapon_Normal.h"
#include "Weapon/Weapon_Explosive.h"
#include "Weapon/Weapon_Concussive.h"
#include "Weapon/Weapon_Spell.h"


const std::string WeaponComp::COMPONENT_NAME = "WeaponComp";

WeaponComp::WeaponComp(Actor* actor)
    : IActorComp(actor)
{
    actor->mWeaponComp = this;
}

WeaponComp::~WeaponComp() {

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




