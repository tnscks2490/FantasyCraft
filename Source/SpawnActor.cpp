#include "pch.h"
#include "World.h"
#include "Actor.h"
#include "DrawComp.h"
#include "MoveComp.h"
#include "UnitCompList.h"

Actor* SpawnCursor(ax::Node* parent)
{
    Actor* actor      = new Actor;
    actor->mActorType = ActorType::SCV;
    actor->mID        = TcpClient::get()->GetID();
    actor->charNum    = 0;

    auto draw = new DrawComp(actor);

    auto node = draw->CreateRootNode();
    parent->addChild(node, 1.0f);

    auto body       = draw->CreatePhysicsNode(ax::Vec2(32, 32));
    auto anim       = draw->CreateAnimNode(ECharName::Cursor, ECharAct::Idle, ECharDir::Face, "Anim");


    return actor;
}

Actor* SpawnSCV(ax::Node* parent, PK_Data data)
{
    Actor* actor = new Actor;
    actor->mActorType = ActorType::SCV;
    actor->mID     = data.ClientID;
    actor->charNum = data.input;

    auto draw = new DrawComp(actor);

    auto node = draw->CreateRootNode();
    parent->addChild(node, 1.0f);

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
    parent->addChild(node, 0.2f);

    auto body       = draw->CreatePhysicsNode(ax::Vec2(16, 16));
    auto anim       = draw->CreateAnimNode(ECharName::Marine);
    auto selectanim = draw->CreateAnimNode(ECharName::Select, "SelectNode");
    selectanim->setVisible(false);

    auto move = new MoveComp(actor);
    auto unit = new MarineComp(actor);
    unit->SetUnitStatus(40, 0, 0, 6, 0);


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
    parent->addChild(node,0.1f);

    auto body       = draw->CreatePhysicsNode(ax::Vec2(16, 16));
    auto anim       = draw->CreateAnimNodeByIndex(ECharName::CommandCenter,0);
    //auto anim       = draw->CreateAnimNode(ECharName::CommandCenter, ECharAct::Idle, ECharDir::Face);
    // 뭐가 문젠지 모르겠음
    auto selectanim = draw->CreateAnimNode(ECharName::Select, "SelectNode");
    selectanim->setVisible(false);

    auto command = new CommandCenterComp(actor);
    auto move = new MoveComp(actor);
    move->IsOn   = false;

    UserData* mUserData = new UserData;
    mUserData->mActor   = actor;
    node->setUserData(mUserData);

    World::get()->Actor_PushBack(actor);
    return actor;
}

Actor* SpawnCommandCenter(ax::Node* parent)
{
    Actor* actor   = new Actor;
    actor->mID     = TcpClient::get()->GetID();
    actor->charNum = 0;

    auto draw = new DrawComp(actor);

    auto node = draw->CreateRootNode();
    parent->addChild(node, 0.1f);

    auto body = draw->CreatePhysicsNode(ax::Vec2(16, 16));
    auto anim = draw->CreateAnimNodeByIndex(ECharName::CommandCenter, 0);
    // auto anim       = draw->CreateAnimNode(ECharName::CommandCenter, ECharAct::Idle, ECharDir::Face);
    //  뭐가 문젠지 모르겠음
    auto selectanim = draw->CreateAnimNode(ECharName::Select, "SelectNode");
    selectanim->setVisible(false);

    auto command = new CommandCenterComp(actor);
    auto move    = new MoveComp(actor);
    move->IsOn   = false;

    UserData* mUserData = new UserData;
    mUserData->mActor   = actor;
    node->setUserData(mUserData);

    World::get()->Actor_PushBack(actor);
    return actor;
}
