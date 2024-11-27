#pragma once
#include "PrePacket.h"
class Actor;


class World
{
public:
    World();
    ~World();

    static World* get();
    void update(float delta);


    Actor* CreateActor(ax::Node* parent, PK_Data data);

    void PrintActorList();

public:
    std::vector<Actor*> w_ActorList;
};

