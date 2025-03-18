#pragma once
#include "IActorComp.h"
#include "Weapon/Weapon.h"

class WeaponComp : public IActorComp
{
public:
    const static std::string COMPONENT_NAME;

	WeaponComp(Actor* actor);
    ~WeaponComp();

    virtual void MessageProc(ActorMessage& msg) override;
    virtual void update(float delta) override;


    void SelectWeapon();
    void TakeAimAndShoot() const;

    void AddWeapon(WeaponType type);
    void DoAction();



public:
    std::vector<Weapon*> mWeaponList;
    Weapon* mCurWeapon = nullptr;

};

