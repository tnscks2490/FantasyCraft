#include "pch.h"
#include "World.h"
#include "Actor.h"
#include "DrawComp.h"
#include "MoveComp.h"
#include "UnitCompList.h"

Actor* SpawnSCV(ax::Node* parent, PK_Data data)
{
    Actor* actor = new Actor;
    actor->mID     = data.ClientID;
    actor->charNum = data.input;

    auto draw = new DrawComp(actor);

    auto node = draw->CreateRootNode();
    parent->addChild(node);

    auto body = draw->CreatePhysicsNode(ax::Vec2(16, 16));
    auto anim       = draw->CreateAnimNode(ECharName::SCV, ECharAct::Idle, ECharDir::S, "Anim");
    auto selectanim = draw->CreateAnimNode(ECharName::Select, "SelectNode");
    selectanim->setVisible(false);

    auto move = new MoveComp(actor);
    auto unit = new SCVComp(actor);

    UserData* mUserData = new UserData;
    mUserData->mActor   = actor;
    node->setUserData(mUserData);

    World::get()->Actor_PushBack(actor);
    return actor;
}

Actor* SpawnMarine(ax::Node* parent, PK_Data data)
{
    Actor* actor = new Actor;
    actor->mID     = data.ClientID;
    actor->charNum = data.input;

    auto draw = new DrawComp(actor);

    auto node = draw->CreateRootNode();
    parent->addChild(node);

    auto body       = draw->CreatePhysicsNode(ax::Vec2(16, 16));
    auto anim       = draw->CreateAnimNode(ECharName::Marine);
    auto selectanim = draw->CreateAnimNode(ECharName::Select, "SelectNode");
    selectanim->setVisible(false);

    auto move = new MoveComp(actor);
    //auto unit = new MarineComp(actor);

    UserData* mUserData = new UserData;
    mUserData->mActor = actor;
    node->setUserData(mUserData);

    World::get()->Actor_PushBack(actor);
    return actor;
}

Actor* SpawnCommandCenter(ax::Node* parent, PK_Data data)
{
    Actor* actor   = new Actor;
    actor->mID     = data.ClientID;
    actor->charNum = data.input;

    auto draw = new DrawComp(actor);

    auto node = draw->CreateRootNode();
    parent->addChild(node);

    auto body       = draw->CreatePhysicsNode(ax::Vec2(16, 16));
    auto anim       = draw->CreateAnimNode(ECharName::CommandCenter);
    auto selectanim = draw->CreateAnimNode(ECharName::Select, "SelectNode");
    selectanim->setVisible(false);

    auto move = new MoveComp(actor);
    //auto unit = new MarineComp(actor);

    UserData* mUserData = new UserData;
    mUserData->mActor   = actor;
    node->setUserData(mUserData);

    World::get()->Actor_PushBack(actor);
    return actor;
}
