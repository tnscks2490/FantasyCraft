#include "pch.h"
#include "World.h"
#include "Actor.h"
#include "MoveComp.h"


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
    Actor* actor = new Actor();
    parent->addChild(actor->mRoot);

    auto sprite = ax::Sprite::create("Farmer.png"sv);
    actor->mRoot->setPosition(500, 500);
    actor->mRoot->addChild(sprite);

    actor->mID = data.ClientID;
    actor->charNum = data.input;

    auto move = new MoveComp(actor);

    auto drawNode = ax::DrawNode::create();
    drawNode->drawRect(ax::Vec2(-16, -16), ax::Vec2(16, 16), ax::Color4F::RED);
    actor->mRoot->addChild(drawNode);


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


