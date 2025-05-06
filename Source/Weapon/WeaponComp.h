#pragma once
#include "IActorComp.h"
#include "Weapon/Weapon.h"

class WeaponComp : public IActorComp
{
public:

	WeaponComp(Actor* actor);
    ~WeaponComp();

    virtual void MessageProc(ActorMessage& msg) override;
    virtual void update(float delta) override;


    void SelectWeapon();
    void TakeAimAndShoot() const;


    void AddWeapon(WeaponType type);
    void DoAction();

    WeaponType ClassifyWeapon(ActorType type);


public:
    std::vector<Weapon*> mWeaponList;
    Weapon* mCurWeapon = nullptr;

};

