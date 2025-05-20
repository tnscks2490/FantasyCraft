#include "pch.h"
#include "World.h"
#include "Actor.h"
#include "MoveComp.h"
#include "DrawComp.h"
#include "UnitComp.h"
#include "SCVComp.h"
#include "PathFind.h"
#include "CommandCenterComp.h"




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
    if (mPath)
        mPath->update(delta);
    if (w_ActorList.size() > 0 || IsAddActors)
    {

        //인덱스로 추정해서 찾아서 삭제하기
        if (IsDeleteActors)
        {
            for (auto& ac : w_Wait_DeleteActors)
            {
                for (auto& AliveActor : w_ActorList)
                {
                    if (ac == AliveActor)
                    {
                        delete ac;
                        ac = nullptr;
                        AliveActor = nullptr;
                    }
                }

                /*if (ac != nullptr)
                {
                    ac->~Actor();
                    ac = nullptr;
                }*/
            }
            //IsAddActors = false;
            //w_Wait_AddActors.clear();
        }

        for (auto actor : w_ActorList)
        {
            if (actor)
                actor->update(delta);
        }

        if (IsAddActors)
        {
            for (auto ac : w_Wait_AddActors)
            {
                if (ac != nullptr)
                {
                    w_ActorList.push_back(ac);
                    ac == nullptr;
                }
            }
            IsAddActors = false;
            w_Wait_AddActors.clear();
        }
    }
}

void World::Actor_PushBack(Actor* actor)
{
    for (auto ac : w_Wait_AddActors)
    {
        if (ac == nullptr)
        {
            ac = actor;
            actor->idx = w_ActorList.size();
            IsAddActors = true;
            return;
        }
    }
    w_Wait_AddActors.push_back(actor);
    actor->idx = w_ActorList.size();
    IsAddActors = true;

    //for (auto ac : w_ActorList)
    //{
    //    if (ac == nullptr)
    //    {
    //        ac          = actor;
    //        actor->idx  = w_ActorList.size();
    //        IsAddActors = true;
    //        return;
    //    }
    //}
    //w_ActorList.push_back(actor);
    //actor->idx  = w_ActorList.size();
    //IsAddActors = true;
}

void World::Actor_PushBackDelete(Actor* actor)
{
    auto mActor = actor;
    for (auto ac : w_Wait_DeleteActors)
    {
        if (ac == nullptr)
        {
            ac          = actor;
            ac->isDead = true;
            return;
        }
    }
    w_Wait_DeleteActors.push_back(actor);
    IsDeleteActors = true;
    mActor->isDead = true;
    //actor->idx = w_ActorList.size();
    // IsAddActors = true;
}

void World::PrintActorList()
{
    for (auto actor : w_ActorList)
    {
        if (actor)
            printf("액터 있음 : %d\n", actor->charNum);
    }
}

void World::test(ax::Node* node)
{
    printf("안녕");
}

World::World()
{
    auto director = ax::Director::getInstance();
    director->getScheduler()->scheduleUpdate(this, -1, false);
}

World::~World() {}
