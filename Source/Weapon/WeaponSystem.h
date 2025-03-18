#pragma once
#include "IActorComponent.h"
#include "Weapon/Weapon.h"

class WeaponSystem : public IActorComponent
{
public:
    const static std::string COMPONENT_NAME;

	WeaponSystem(Actor* actor);
    ~WeaponSystem();

    virtual void update(float delta) override;

    void SelectWeapon();
    void TakeAimAndShoot() const;

    void AddWeapon(WeaponType type);
    void DoAction();



public:
    std::vector<Weapon*> mWeaponList;
    Weapon* mCurWeapon = nullptr;

};

