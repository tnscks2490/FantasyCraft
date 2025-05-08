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
    bool DoAttack(Actor* mTarget);
    void DoAction();

    WeaponType ClassifyWeapon(ActorType type);

    void SetRange(float range) { mRange = range * 32; }

    void SetRangeByType(ActorType type);

public:
    std::vector<Weapon*> mWeaponList;
    Weapon* mCurWeapon = nullptr;

    float mRange = 0;

};

