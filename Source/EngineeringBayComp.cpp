#include "pch.h"
#include "Actor.h"
#include "EngineeringBayComp.h"
#include "DrawComp.h"

EngineeringBayComp::EngineeringBayComp(Actor* actor)
    : UnitComp(actor)
{
    actor->mUnitComp = this;
    SetUnitStatus(ActorType::EngineeringBay);
    mUnitName = "Terran EngineeringBay";

    BuildAnimChangeTime = MaxBuildTime / 4.f;
}

EngineeringBayComp::~EngineeringBayComp() {}

void EngineeringBayComp::MessageProc(ActorMessage& msg)
{
    switch (msg.msgType)
    {
    case MsgType::Contacted:
    {
    }
    break;
    case MsgType::Build_Start:
    {
        if (mBuilder == nullptr && msg.sender->mActorType == ActorType::SCV)
        {
            if (msg.sender->mUnitComp->mCurAction == ActionState::Building)
            {
                mBuilder   = msg.sender;
                mCurAction = ActionState::Building;
                cmdLocked  = true;
            }
        }

        ActorMessage Msg = {MsgType::SendInfo, mActor, nullptr, nullptr};
        SendActorMessage(msg.sender, Msg);
    }
    break;
    case MsgType::Build_GetBuilder:
    {
        if (mBuilder == nullptr)
        {
            mBuilder   = msg.sender;
            mCurAction = ActionState::Building;
            cmdLocked  = true;
        }
    }
    break;

    case MsgType::Build_Continue:
    {
        if (mBuilder == nullptr)
        {
            mBuilder = msg.sender;
            cmdLocked = true;
        }
    }
    break;

    case MsgType::Build_Cancel:
    {
        if (!isBuild)
            mBuilder = nullptr;

        cmdLocked = false;
    }
    break;
    case MsgType::Upgrade_Bionic_AT:
    {
        isUpgrade = true;
        mCurAction = ActionState::Upgrade;

        if (BionicAT == 0)
        {
            mCurUpgrade = UpgradeType::BionicAT1;
            MaxUT = FindUpgradeBP(UpgradeType::BionicAT1).buildTime;
        }
        else if (BionicAT == 1)
        {
            mCurUpgrade = UpgradeType::BionicAT1;
            MaxUT = FindUpgradeBP(UpgradeType::BionicAT2).buildTime;

        }
        else if (BionicAT == 2)
        {
            mCurUpgrade = UpgradeType::BionicAT1;
            MaxUT       = FindUpgradeBP(UpgradeType::BionicAT3).buildTime;
        }

    } break;
    case MsgType::Upgrade_Bionic_DF:
    {
        isUpgrade  = true;
        mCurAction = ActionState::Upgrade;

        if (BionicDF == 0)
        {
            mCurUpgrade = UpgradeType::BionicDF1;
            MaxUT       = FindUpgradeBP(UpgradeType::BionicDF1).buildTime;
        }
        else if (BionicDF == 1)
        {
            mCurUpgrade = UpgradeType::BionicDF2;
            MaxUT       = FindUpgradeBP(UpgradeType::BionicDF2).buildTime;
        }
        else if (BionicDF == 2)
        {
            mCurUpgrade = UpgradeType::BionicDF3;
            MaxUT       = FindUpgradeBP(UpgradeType::BionicDF3).buildTime;
        }
    } break;
    case MsgType::Cancel:
    {
        if (IsBuild())
        {
            isUpgrade   = false;
            MaxUT       = 0;
            CurUT       = 0;
            mCurUpgrade = UpgradeType::None;
            mCurAction  = ActionState::Idle;
        }
        
    }
    break;
    default:
        break;
    }
}

void EngineeringBayComp::update(float delta)
{
    if (!isBuild && mBuilder)
    {
        if (mBuilder->mActorType == ActorType::SCV)
        {
            mTimer += delta;
            BuildingTime += delta;
            if (mTimer >= 1.0f)
            {
                mTimer = 0.f;
                mStatus.HP += (int)(mStatus.MaxHP * 0.9f) / MaxBuildTime;
                if (BuildingTime >= MaxBuildTime)
                {
                    ActorMessage msg = {MsgType::Build_Complete, mActor, nullptr, nullptr};
                    SendActorMessage(mBuilder, msg);

                    isBuild    = true;
                    mCurAction = ActionState::Idle;
                    mBuilder   = nullptr;
                    cmdLocked  = false;
                }
                else
                {
                    changeImageIdx = BuildingTime / BuildAnimChangeTime;
                    if (changeImageIdx != drawidx)
                    {
                        drawidx = changeImageIdx;
                        mActor->mDrawComp->ChangeAnimByIndex(ECharName::EngineeringBay, ECharAct::Building,
                                                             ECharDir::Face, drawidx);
                    }
                }

                printf("%f초 \n", BuildingTime);
            }
        }
    }

    if (isUpgrade)
    {
        CurUT += delta;
        if (CurUT >= MaxUT)
        {
            mCurAction = ActionState::Idle;
            isUpgrade  = false;
            switch (mCurUpgrade)
            {
            case UpgradeType::BionicAT1:
            case UpgradeType::BionicAT2:
            case UpgradeType::BionicAT3:
                BionicAT++; // 이후 서버에 전송하는 내용 넣을것
                break;
            case UpgradeType::BionicDF1:
            case UpgradeType::BionicDF2:
            case UpgradeType::BionicDF3:
                BionicDF++; // 이후 서버에 전송하는 내용 넣을것
                break;
            }
            CurUT = 0;
            MaxUT = 0;
        }

    }
}

