#include "pch.h"
#include "Weapon/Weapon.h"
#include "Actor.h"


void Weapon::CoolTime(float delta)
{
    if (IsUsing)
    {
        mTimer += delta;
        if (mTimer >= mCoolTime)
        {
            mTimer  = 0.000f;
            mActor->mUnitComp->cmdLocked  = false;
            IsUsing   = false;

            ActorMessage msg = {MsgType::WeaponIsReady, mActor, nullptr, nullptr};
            SendActorMessage(mActor, msg);
            //mActor->mUnitComp->mCurAction = ActionState::Idle;
        }
    }
}

void Weapon::SetAttackDelay(ActorType type)
{
    switch (type)
    {
    // case ActorType::Medic:       break;
    // case ActorType::Bunker:        break;
    case ActorType::FireBat:  mCoolTime = 0.916f; break;
    case ActorType::SCV:      mCoolTime = 0.625f; break;
    case ActorType::Marine:   mCoolTime = 0.916f; break;
    case ActorType::Ghost:    mCoolTime = 0.916f; break;
    case ActorType::Vulture:  mCoolTime = 0.916f; break;
    case ActorType::Tank:     mCoolTime = 1.25f;  break;
    case ActorType::Goliath:  mCoolTime = 0.916f; break;
    case ActorType::Wraith:   mCoolTime = 0.916f; break;
    case ActorType::Valkyrie: mCoolTime = 2.5f;   break;
    }

}
