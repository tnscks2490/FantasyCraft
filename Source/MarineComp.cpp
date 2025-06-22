#include "pch.h"
#include "Actor.h"
#include "MarineComp.h"
#include "Goal/Base/GoalComp.h"
#include "DrawComp.h"
#include "SensorComp.h"

MarineComp::MarineComp(Actor* actor)
    : UnitComp(actor)
{
    actor->mUnitComp = this;
    SetUnitStatus(ActorType::Marine);
    mUnitName = "Terran Marine";
}

MarineComp::~MarineComp()
{
}

void MarineComp::update(float delta)
{

}

void MarineComp::MessageProc(ActorMessage& msg)
{
    
    switch (msg.msgType)
    {
    case MsgType::SetTarget:
    {
        //TODO: 여기 해결할것
        
        auto mTarget = msg.sender;

        if (mTarget == mActor)
            return;
        
    } break;
    case MsgType::SetAttackTarget:
    {

        mAttackTarget = msg.sender;

        if (mAttackTarget && !mAttackTarget->isDead)
        {
            AddGoal_MoveAndAttack(mActor, mAttackTarget);
        }

    }break;

    case MsgType::AttackTarget:
    {
        AttackTarget(msg.sender);  
    }break;
    case MsgType::Attack:
    {
        int damage = msg.sender->mUnitComp->mStatus.AT - mStatus.DF;
        if (damage <= 0)
            damage = 1;

        PK_Data data;
        data.ClientID = mActor->GetID();
        data.input    = 5;
        data.pos      = ax::Vec2(mActor->GetIDX(), damage);
        TcpClient::get()->SendMessageToServer(data);

        //SCVHpChange();
        mActor->mDrawComp->CreateDemageNode(msg.sender->mActorType);

        if (mActor->mUnitComp->mStatus.HP <= 0)
        {
            PK_Data data;
            data.ClientID = mActor->GetID();
            data.input    = 13;
            data.pos      = ax::Vec2(mActor->GetIDX(), 0);
            TcpClient::get()->SendMessageToServer(data);
        }
    } break;
    case MsgType::ImDead:
    {
        mAttackTarget = nullptr;
        mActor->mSensorComp->mTarget = nullptr;
        ChangeAction(ActionState::Idle);
        //SearchNextTarget();
    }
    break;
    case MsgType::ImNotDead:
    {
        mAttackTarget = msg.sender;
    } break;
    case MsgType::WeaponIsReady:
    {
        AddGoal_MoveAndAttack(mActor, mAttackTarget);
    }
    default:
        break;
    }
}

void MarineComp::SearchNextTarget()
{
    if (mAttackTarget)
        return;
    else
    {
        mActor->mSensorComp->ReStartSensor();
    }
}

void MarineComp::AttackTarget(Actor* Target)
{
    if (mActor->mWeaponComp->DoAttack(Target))
    {
        auto pos = Target->GetPosition() - mActor->GetPosition();
        mActor->mDrawComp->ChangeCurDir(pos);   
    }
}

void MarineComp::WaitCoolTime()
{

}
