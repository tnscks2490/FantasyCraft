#include "pch.h"
#include "World.h"
#include "Actor.h"
#include "MoveComp.h"
#include "DrawComp.h"

namespace
{
static World* g_World = nullptr;
}

World* World::get()
{
    if (!g_World) g_World = new World;
    return g_World;
}

void World::update(float delta)
{
    if (w_ActorList.size() > 0)
    {
        for (auto actor : w_ActorList)
        {
            actor->update(delta);
        }
    }
}

Actor* World::CreateActor(ax::Node* parent, PK_Data data)
{
    // 빈 엑터 생성
    Actor* actor = new Actor();

    // 드로우컴포넌트 및 루트 노드 생성 후 씬에 붙이기
    auto draw = new DrawComp(actor);

    // 루트 노드 생성 및 메인씬에 붙이기(그리기 위함)
    auto node = draw->CreateRootNode();
    draw->mRoot->setPosition(500, 500);
    parent->addChild(node);


    // 몸통부분 생성 및 루트노드에 붙이기
    auto body = draw->CreatePhysicsNode(ax::Vec2(16,16));
    auto anim = draw->CreateAnimNode(ECharName::Farmer);
    
    /////////////////////////////////////////////////
    // 스프라이트 생성후 루트 노드에 붙이기



    // 엑터에 클라이언트 데이터 넣어주기
    actor->mID = data.ClientID;
    actor->charNum = data.input;

    // 무브컴포넌트 생성
    auto move = new MoveComp(actor);


    // 단순 루트노드 찾기용 코드
    auto drawNode = ax::DrawNode::create();
    drawNode->drawRect(ax::Vec2(-8, -8), ax::Vec2(8, 8), ax::Color4F::RED);
    node->addChild(drawNode);


    // 월드 엑터리스트에 이 엑터 넣어주기
    w_ActorList.push_back(actor);

    return actor;
}

void World::PrintActorList()
{
    for (auto actor : w_ActorList)
    {
        if (actor)
            printf("액터 있음 : %d\n", actor->charNum);
    }
}


World::World()
{
    auto director = ax::Director::getInstance();
    director->getScheduler()->scheduleUpdate(this, -1, false);
}

World::~World() {}


