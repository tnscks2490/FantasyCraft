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
    void PrintActorList();


public:
    std::vector<Actor*> w_Wait_AddActors;
    std::vector<Actor*> w_ActorList;
    std::vector<Actor*> w_Wait_DeleteActors;
    PathFind* mPath;


public:
    bool IsAddActors = false;
    bool IsDeleteActors = false;
};


Actor* SpawnCursor(ax::Node* parent);



Actor* SpawnSCV(ax::Node* parent, PK_Data data);
Actor* SpawnMarine(ax::Node* parent, PK_Data data);
Actor* SpawnCommandCenter(ax::Node* parent, PK_Data data);
Actor* SpawnCommandCenter(ax::Node* parent);



// 건물 설치할때 블루프린트 스폰하기
Actor* BPCommandCenter(ax::Node* parent);
