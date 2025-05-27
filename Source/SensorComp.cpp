#include "pch.h"
#include "SensorComp.h"
#include "SensorMemory.h"
#include "Goal/Base/GoalComp.h"
#include "Actor.h"

SensorComp::SensorComp(Actor* actor)
    :IActorComp(actor)
{
    actor->mSensorComp = this;
    SetSightByType(actor->mActorType);
    CreateSightNode();
}

SensorComp::~SensorComp()
{
    mSenserMemory = nullptr;
    mTarget       = nullptr;
    if (mActor)
        mActor->mSensorComp = nullptr;
}


void SensorComp::update(float delta)
{

}

void SensorComp::MessageProc(ActorMessage& msg)
{
    switch (msg.msgType)
    {
    case MsgType::Separate:
    case MsgType::Contacted:
    {
        if (msg.sender->mActorType == ActorType::Cursor)
            return;
        if (msg.sender->mID != mActor->mID)
        {
            AddGoal_MoveAndAttack(mActor, msg.sender);
        }
    }
    break;
    default:
        break;
    }
}

void SensorComp::SetSightByType(ActorType type)
{
    switch (type)
    {
    case ActorType::SCV:             SetSight(7);   break;
    case ActorType::Marine:          SetSight(7);   break;
    case ActorType::Medic:           SetSight(10);  break;
    case ActorType::FireBat:         SetSight(5);   break;
    case ActorType::Ghost:           SetSight(10);  break;
    case ActorType::Vulture:         SetSight(8);   break;
    case ActorType::Tank:            SetSight(10);  break;
    case ActorType::Goliath:         SetSight(8);   break;
    case ActorType::Wraith:          SetSight(8);   break;
    case ActorType::Valkyrie:        SetSight(8);   break;
    case ActorType::DropShip:        SetSight(8);   break;
    case ActorType::ScienceVessel:   SetSight(11);  break;
    case ActorType::BattleCruiser:   SetSight(10);  break;
    case ActorType::CommandCenter:   SetSight(9);   break;
    case ActorType::SupplyDepot:     SetSight(8);   break;
    case ActorType::Academy:         SetSight(8);   break;
    case ActorType::Armory:          SetSight(8);   break;
    case ActorType::Barrack:         SetSight(9);   break;
    case ActorType::Bunker:          SetSight(7);   break;
    case ActorType::EngineeringBay:  SetSight(8);   break;
    case ActorType::StarPort:        SetSight(9);   break;
    case ActorType::Factory:         SetSight(9);   break;
    case ActorType::ScienceFacility: SetSight(8);   break;
    case ActorType::Refinery:        SetSight(8);   break;
    default:  break;
    }
}
ax::Node* SensorComp::CreateSightNode()
{
    auto root = mActor->GetRoot();

    if (root != nullptr)
    {
        auto sNode = ax::Node::create();
        sNode->setName("SensorNode");
        root->addChild(sNode, 1);

        auto sBody = ax::PhysicsBody::createCircle(mSight);
        sBody->setContactTestBitmask(0xFFFFFFFF);
        sBody->setDynamic(false);
        sNode->setPhysicsBody(sBody);
        sNode->setTag(100);

        ax::DrawNode* circle = ax::DrawNode::create();
        circle->drawCircle(ax::Vec2::ZERO, mSight,360, 100,true,ax::Color4B::RED);
        sNode->addChild(circle,1);

        return sNode;
    }
    return nullptr;
}
//TODO:터렛은 11임 공격사거리 7
