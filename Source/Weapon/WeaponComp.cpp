#include "pch.h"
#include "Actor.h"
#include "WeaponComp.h"
#include "Weapon/Weapon.h"

const std::string WeaponComp::COMPONENT_NAME = "WeaponComp";

WeaponComp::WeaponComp(Actor* actor)
    : IActorComp(actor)
{
    actor->mWeaponComp = this;
}

WeaponComp::~WeaponComp() {

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
    Weapon* weapon;

    switch (type)
    {
    case WeaponType::None:
        break;
    case WeaponType::Sword:
        break;
    case WeaponType::Pick:
        break;
    case WeaponType::Axe:
        break;
    case WeaponType::WateringCan:
        break;
    case WeaponType::Bow:
        break;
    case WeaponType::Torch:
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




