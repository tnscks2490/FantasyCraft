#include "pch.h"
#include "Actor.h"
#include "WeaponSystem.h"
#include "SceneComp.h"
#include "Weapon/Weapon.h"
#include "Weapon/Weapon_Sword.h"

const std::string WeaponSystem::COMPONENT_NAME = "WeaponSystem";

WeaponSystem::WeaponSystem(Actor* actor)
    : IActorComponent(actor)
{
    mCompName = COMPONENT_NAME;

    actor->mWeaponSystem = this;


    AddWeapon(WeaponType::Sword);
}

WeaponSystem::~WeaponSystem() 
{

}

void WeaponSystem::update(float delta)
{
    TakeAimAndShoot();
    if (mCurWeapon) mCurWeapon->update(delta);
}

void WeaponSystem::SelectWeapon() 
{

}

void WeaponSystem::TakeAimAndShoot() const 
{
}

void WeaponSystem::AddWeapon(WeaponType type)
{
    Weapon* weapon;

    switch (type)
    {
    case WeaponType::None:
        break;
    case WeaponType::Sword:
        weapon = new Weapon_Sword(mActor);
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

void WeaponSystem::DoAction()
{
    if (mCurWeapon)
        mCurWeapon->Use();
}




