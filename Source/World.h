#pragma once
#include "PrePacket.h"

class Actor;
struct UserData
{
    Actor* mActor;
};

class World
{
public:
    World();
    ~World();

    static World* get();
    void update(float delta);


    void Actor_PushBack(Actor* actor);
    Actor* CreateActor(ax::Node* parent, PK_Data data);

    void PrintActorList();

public:
    std::vector<Actor*> w_ActorList;
};

