#include "pch.h"
#include "World.h"
#include "Actor.h"
#include "DrawComp.h"
#include "MoveComp.h"
#include "GoalComp.h"
#include "WeaponComp.h"
#include "BPComp.h"
#include "CursorComp.h"
#include "UnitCompList.h"

Actor* SpawnCursor(ax::Node* parent)
{
    Actor* actor      = new Actor;
    actor->mActorType = ActorType::Cursor;
    actor->mID        = TcpClient::get()->GetID();
    actor->charNum    = 0;

    auto draw = new DrawComp(actor);

    auto node = draw->CreateRootNode();
    parent->addChild(node, 10.0f);

    auto body       = draw->CreatePhysicsNode(ax::Vec2(16, 16));
    body->setTag(-1);
    body->setName("Cursor");
    auto anim       = draw->CreateAnimNode(ECharName::Cursor, ECharAct::Idle, ECharDir::Face, "Anim");
    auto cursor = new CursorComp(actor);
    draw->CreateCursorRect(ax::Vec2(0, 0), ax::Vec2(0, 0));

    //auto Tanim = draw->CreateAnimNode(ECharName::Cursor, ECharAct::Target, ECharDir::Face, "TargetAnim");
    //Tanim->setVisible(false);


    UserData* mUserData = new UserData;
    mUserData->mActor   = actor;
    node->setUserData(mUserData);


    return actor;
}

Actor* SpawnSCV(ax::Node* parent, PK_Data data)
{
    Actor* actor = new Actor;
    actor->mActorType = ActorType::SCV;
    actor->mCategory  = UnitCategory::Unit;
    actor->mID     = data.ClientID;
    actor->charNum = data.input;

    auto draw = new DrawComp(actor);

    auto node = draw->CreateRootNode();
    parent->addChild(node, 1.0f);

    auto body = draw->CreatePhysicsNode(ax::Vec2(16, 16));

    auto anim       = draw->CreateAnimNode(ECharName::SCV, ECharAct::Idle, ECharDir::S, "Anim");
    // 선택 표기 타원의 위치는 바디사이즈의 1/2, 반지름의 크기도 바디사이즈의 1/2로 설정할것
    auto selectanim = draw->CreateSelectedNode();

    auto hpbar = draw->CreateHPBarByIndex(ECharName::Marine, 0);
    hpbar->setPosition(ax::Vec2(0, -20));
    selectanim->addChild(hpbar);


    
    auto goal = new GoalComp(actor);
    auto move = new MoveComp(actor);
    auto unit = new SCVComp(actor);
    auto weapon = new WeaponComp(actor);
    weapon->AddWeapon(WeaponType::Normal);


    UserData* mUserData = new UserData;
    mUserData->mActor   = actor;
    node->setUserData(mUserData);

    World::get()->Actor_PushBack(actor);
    return actor;
}

Actor* SpawnMarine(ax::Node* parent, PK_Data data)
{
    Actor* actor = new Actor;
    actor->mActorType = ActorType::Marine;
    actor->mCategory  = UnitCategory::Unit;
    actor->mID     = data.ClientID;
    actor->charNum = data.input;

    auto draw = new DrawComp(actor);

    auto node = draw->CreateRootNode();
    parent->addChild(node, 1.f);
    
    auto body       = draw->CreatePhysicsNode(ax::Vec2(16, 16));
    auto anim = draw->CreateAnimNode(ECharName::Marine, ECharAct::Idle, ECharDir::S, "Anim");
    auto selectanim = draw->CreateSelectedNode();

    auto hpbar      = draw->CreateHPBarByIndex(ECharName::Marine, 0);
    hpbar->setPosition(ax::Vec2(0, -20));
    selectanim->addChild(hpbar);


    auto goal           = new GoalComp(actor);
    auto move           = new MoveComp(actor);
    auto unit           = new MarineComp(actor);
    auto weapon        = new WeaponComp(actor);
    weapon->AddWeapon(WeaponType::Normal);



    UserData* mUserData = new UserData;
    mUserData->mActor = actor;
    node->setUserData(mUserData);

    World::get()->Actor_PushBack(actor);
    return actor;
}

Actor* SpawnCommandCenter(ax::Node* parent, PK_Data data)
{
    Actor* actor   = new Actor;
    actor->mActorType = ActorType::CommandCenter;
    actor->mCategory  = UnitCategory::Building;
    actor->mID     = data.ClientID;
    actor->charNum = data.input;

    auto draw = new DrawComp(actor);

    auto node = draw->CreateRootNode();
    parent->addChild(node,0.1f);

    auto body       = draw->CreatePhysicsNode(ax::Vec2(64, 64));


    auto selectanim = ax::DrawNode::create();
    selectanim->drawCircle(ax::Vec2(0, -8), 48.f, 360.f, 20, false, 1.5f, 1.0f, ax::Color4B::GREEN);
    selectanim->setName("Select");
    selectanim->setVisible(false);
    node->addChild(selectanim);


    auto anim       =  draw->CreateAnimNodeByIndex(ECharName::CommandCenter, ECharAct::Building, 0);

    auto command = new CommandCenterComp(actor);
    auto move = new MoveComp(actor);
    move->IsOn   = false;

    UserData* mUserData = new UserData;
    mUserData->mActor   = actor;
    node->setUserData(mUserData);

    World::get()->Actor_PushBack(actor);

    return actor;
}

Actor* SpawnAcademy(ax::Node* parent, PK_Data data)
{
    Actor* actor      = new Actor;
    actor->mActorType = ActorType::Academy;
    actor->mCategory  = UnitCategory::Building;
    actor->mID        = data.ClientID;
    actor->charNum    = data.input;

    auto draw = new DrawComp(actor);

    auto node = draw->CreateRootNode();
    parent->addChild(node, 0.1f);

    auto body = draw->CreatePhysicsNode(ax::Vec2(64, 64));

    auto selectanim = ax::DrawNode::create();
    selectanim->drawCircle(ax::Vec2(0, -8), 32.f, 360.f, 20, false, 1.5f, 1.0f, ax::Color4B::GREEN);
    selectanim->setName("Select");
    selectanim->setVisible(false);
    node->addChild(selectanim);

    auto anim = draw->CreateAnimNodeByIndex(ECharName::Academy, ECharAct::Building, 0);

    auto command = new AcademyComp(actor);

    UserData* mUserData = new UserData;
    mUserData->mActor   = actor;
    node->setUserData(mUserData);

    World::get()->Actor_PushBack(actor);

    return actor;
}

Actor* SpawnArmory(ax::Node* parent, PK_Data data)
{
    Actor* actor      = new Actor;
    actor->mActorType = ActorType::Armory;
    actor->mCategory  = UnitCategory::Building;
    actor->mID        = data.ClientID;
    actor->charNum    = data.input;

    auto draw = new DrawComp(actor);

    auto node = draw->CreateRootNode();
    parent->addChild(node, 0.1f);

    auto body = draw->CreatePhysicsNode(ax::Vec2(64, 64));

    auto selectanim = ax::DrawNode::create();
    selectanim->drawCircle(ax::Vec2(0, -8), 32.f, 360.f, 20, false, 1.5f, 1.0f, ax::Color4B::GREEN);
    selectanim->setName("Select");
    selectanim->setVisible(false);
    node->addChild(selectanim);

    auto anim = draw->CreateAnimNodeByIndex(ECharName::Armory, ECharAct::Building, 0);

    auto command = new ArmoryComp(actor);

    UserData* mUserData = new UserData;
    mUserData->mActor   = actor;
    node->setUserData(mUserData);

    World::get()->Actor_PushBack(actor);
    return actor;
}

Actor* SpawnBarrack(ax::Node* parent, PK_Data data)
{
    Actor* actor      = new Actor;
    actor->mActorType = ActorType::Barrack;
    actor->mCategory  = UnitCategory::Building;
    actor->mID        = data.ClientID;
    actor->charNum    = data.input;

    auto draw = new DrawComp(actor);

    auto node = draw->CreateRootNode();
    parent->addChild(node, 0.1f);

    auto body = draw->CreatePhysicsNode(ax::Vec2(64, 64));

    auto selectanim = ax::DrawNode::create();
    selectanim->drawCircle(ax::Vec2(0, -8), 32.f, 360.f, 20, false, 1.5f, 1.0f, ax::Color4B::GREEN);
    selectanim->setName("Select");
    selectanim->setVisible(false);
    node->addChild(selectanim);

    auto anim = draw->CreateAnimNodeByIndex(ECharName::Barrack, ECharAct::Building, 0);

    auto command = new BarrackComp(actor);
    auto move    = new MoveComp(actor);
    move->IsOn   = false;

    UserData* mUserData = new UserData;
    mUserData->mActor   = actor;
    node->setUserData(mUserData);

    World::get()->Actor_PushBack(actor);
    return actor;
}

Actor* SpawnBunker(ax::Node* parent, PK_Data data)
{
    Actor* actor      = new Actor;
    actor->mActorType = ActorType::Bunker;
    actor->mCategory  = UnitCategory::Building;
    actor->mID        = data.ClientID;
    actor->charNum    = data.input;

    auto draw = new DrawComp(actor);

    auto node = draw->CreateRootNode();
    parent->addChild(node, 0.1f);

    auto body = draw->CreatePhysicsNode(ax::Vec2(64, 64));

    auto selectanim = ax::DrawNode::create();
    selectanim->drawCircle(ax::Vec2(0, -8), 32.f, 360.f, 20, false, 1.5f, 1.0f, ax::Color4B::GREEN);
    selectanim->setName("Select");
    selectanim->setVisible(false);
    node->addChild(selectanim);

    auto anim = draw->CreateAnimNodeByIndex(ECharName::Bunker, ECharAct::Building, 0);

    auto command = new BunkerComp(actor);


    UserData* mUserData = new UserData;
    mUserData->mActor   = actor;
    node->setUserData(mUserData);

    World::get()->Actor_PushBack(actor);
    return actor;
}

Actor* SpawnEngineeringBay(ax::Node* parent, PK_Data data)
{
    Actor* actor      = new Actor;
    actor->mActorType = ActorType::EngineeringBay;
    actor->mCategory  = UnitCategory::Building;
    actor->mID        = data.ClientID;
    actor->charNum    = data.input;

    auto draw = new DrawComp(actor);

    auto node = draw->CreateRootNode();
    parent->addChild(node, 0.1f);

    auto body = draw->CreatePhysicsNode(ax::Vec2(64, 64));

    auto selectanim = ax::DrawNode::create();
    selectanim->drawCircle(ax::Vec2(0, -8), 32.f, 360.f, 20, false, 1.5f, 1.0f, ax::Color4B::GREEN);
    selectanim->setName("Select");
    selectanim->setVisible(false);
    node->addChild(selectanim);

    auto anim = draw->CreateAnimNodeByIndex(ECharName::EngineeringBay, ECharAct::Building, 0);

    auto command = new EngineeringBayComp(actor);
    auto move    = new MoveComp(actor);
    move->IsOn   = false;

    UserData* mUserData = new UserData;
    mUserData->mActor   = actor;
    node->setUserData(mUserData);

    World::get()->Actor_PushBack(actor);
    return actor;
}

Actor* SpawnSupplyDepot(ax::Node* parent, PK_Data data)
{
    Actor* actor      = new Actor;
    actor->mActorType = ActorType::SupplyDepot;
    actor->mCategory  = UnitCategory::Building;
    actor->mID        = data.ClientID;
    actor->charNum    = data.input;

    auto draw = new DrawComp(actor);

    auto node = draw->CreateRootNode();
    parent->addChild(node, 0.1f);

    auto body = draw->CreatePhysicsNode(ax::Vec2(64, 64));

    auto selectanim = ax::DrawNode::create();
    selectanim->drawCircle(ax::Vec2(0, -8), 32.f, 360.f, 20, false, 1.5f, 1.0f, ax::Color4B::GREEN);
    selectanim->setName("Select");
    selectanim->setVisible(false);
    node->addChild(selectanim);

    auto anim = draw->CreateAnimNodeByIndex(ECharName::SupplyDepot, ECharAct::Building, 0);

    auto command = new SupplyDepotComp(actor);

    UserData* mUserData = new UserData;
    mUserData->mActor   = actor;
    node->setUserData(mUserData);

    World::get()->Actor_PushBack(actor);
    return actor;
}

Actor* SpawnStarPort(ax::Node* parent, PK_Data data)
{
    Actor* actor      = new Actor;
    actor->mActorType = ActorType::StarPort;
    actor->mCategory  = UnitCategory::Building;
    actor->mID        = data.ClientID;
    actor->charNum    = data.input;

    auto draw = new DrawComp(actor);

    auto node = draw->CreateRootNode();
    parent->addChild(node, 0.1f);

    auto body = draw->CreatePhysicsNode(ax::Vec2(64, 64));

    auto selectanim = ax::DrawNode::create();
    selectanim->drawCircle(ax::Vec2(0, -8), 32.f, 360.f, 20, false, 1.5f, 1.0f, ax::Color4B::GREEN);
    selectanim->setName("Select");
    selectanim->setVisible(false);
    node->addChild(selectanim);

    auto anim = draw->CreateAnimNodeByIndex(ECharName::StarPort, ECharAct::Building, 0);

    auto command = new StarPortComp(actor);
    auto move    = new MoveComp(actor);
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

    auto selectanim = ax::DrawNode::create();
    selectanim->drawCircle(ax::Vec2(0, -8), 32.f, 360.f, 20, false, 1.5f, 1.0f, ax::Color4B::GREEN);
    selectanim->setName("Select");
    selectanim->setVisible(false);
    node->addChild(selectanim);


    auto body = draw->CreatePhysicsNode(ax::Vec2(16, 16));
    auto anim = draw->CreateAnimNode(ECharName::CommandCenter, ECharAct::BP, ECharDir::Face, "BPAnim");
    

    auto command = new CommandCenterComp(actor);
    auto move    = new MoveComp(actor);
    move->IsOn   = false;

    UserData* mUserData = new UserData;
    mUserData->mActor   = actor;
    node->setUserData(mUserData);

    World::get()->Actor_PushBack(actor);
    return actor;
}


// Bp생성하고 대형 중형 소형에 따라 피직스 노드 추가할것 
Actor* BPCommandCenter(ax::Node* parent)
{
    Actor* actor = new Actor;
    actor->mActorType = ActorType::BP;
    auto draw = new DrawComp(actor);

    auto node = draw->CreateRootNode();
    parent->addChild(node, 1.f);

    auto body = draw->Create_Big_BPPhysicsNode();
    auto anim = draw->CreateAnimNode(ECharName::CommandCenter, ECharAct::BP, ECharDir::Face, "BPAnim");

    auto bp = new BPComp(actor);

    return actor;
}

Actor* BPEngineeringBay(ax::Node* parent)
{
    Actor* actor      = new Actor;
    actor->mActorType = ActorType::BP;
    auto draw         = new DrawComp(actor);

    auto node = draw->CreateRootNode();
    parent->addChild(node, 1.f);

    auto body = draw->Create_Big_BPPhysicsNode();
    auto anim = draw->CreateAnimNode(ECharName::EngineeringBay, ECharAct::BP, ECharDir::Face, "BPAnim");

    auto bp = new BPComp(actor);

    return actor;
}

Actor* BPStarPort(ax::Node* parent)
{
    Actor* actor      = new Actor;
    actor->mActorType = ActorType::BP;
    auto draw         = new DrawComp(actor);

    auto node = draw->CreateRootNode();
    parent->addChild(node, 1.f);

    auto body = draw->Create_Big_BPPhysicsNode();
    auto anim = draw->CreateAnimNode(ECharName::StarPort, ECharAct::BP, ECharDir::Face, "BPAnim");

    auto bp = new BPComp(actor);

    return actor;
}

Actor* BPSupplyDpot(ax::Node* parent)
{
    Actor* actor      = new Actor;
    actor->mActorType = ActorType::BP;
    auto draw         = new DrawComp(actor);

    auto node = draw->CreateRootNode();
    parent->addChild(node, 1.f);

    auto body = draw->Create_Middle_BPPhysicsNode();
    auto anim = draw->CreateAnimNode(ECharName::SupplyDepot, ECharAct::BP, ECharDir::Face, "BPAnim");

    auto bp = new BPComp(actor);

    return actor;
}

Actor* BPAcademy(ax::Node* parent)
{
    Actor* actor      = new Actor;
    actor->mActorType = ActorType::BP;
    auto draw         = new DrawComp(actor);

    auto node = draw->CreateRootNode();
    parent->addChild(node, 1.f);

    auto body = draw->Create_Big_BPPhysicsNode();
    auto anim = draw->CreateAnimNode(ECharName::Academy, ECharAct::BP, ECharDir::Face, "BPAnim");

    auto bp = new BPComp(actor);

    return actor;
}

Actor* BPArmory(ax::Node* parent)
{
    Actor* actor      = new Actor;
    actor->mActorType = ActorType::BP;
    auto draw         = new DrawComp(actor);

    auto node = draw->CreateRootNode();
    parent->addChild(node, 1.f);

    auto body = draw->Create_Big_BPPhysicsNode();
    auto anim = draw->CreateAnimNode(ECharName::Armory, ECharAct::BP, ECharDir::Face, "BPAnim");

    auto bp = new BPComp(actor);

    return actor;
}

Actor* BPBarrack(ax::Node* parent)
{
    Actor* actor      = new Actor;
    actor->mActorType = ActorType::BP;
    auto draw         = new DrawComp(actor);

    auto node = draw->CreateRootNode();
    parent->addChild(node, 1.f);

    auto body = draw->Create_Big_BPPhysicsNode();
    auto anim = draw->CreateAnimNode(ECharName::Barrack, ECharAct::BP, ECharDir::Face, "BPAnim");

    auto bp = new BPComp(actor);

    return actor;
}

Actor* BPBunker(ax::Node* parent)
{
    Actor* actor      = new Actor;
    actor->mActorType = ActorType::BP;
    auto draw         = new DrawComp(actor);

    auto node = draw->CreateRootNode();
    parent->addChild(node, 1.f);

    auto body = draw->Create_Big_BPPhysicsNode();
    auto anim = draw->CreateAnimNode(ECharName::Bunker, ECharAct::BP, ECharDir::Face, "BPAnim");

    auto bp = new BPComp(actor);

    return actor;
}
