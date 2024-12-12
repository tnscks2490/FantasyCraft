#pragma once
#include "PrePacket.h"

class Actor;
class PathFind;

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
    PathFind* mPath;
};



Actor* SpawnSCV(ax::Node* parent, PK_Data data);
Actor* SpawnMarine(ax::Node* parent, PK_Data data);
Actor* SpawnCommandCenter(ax::Node* parent, PK_Data data);

