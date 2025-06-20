#pragma once
#include "PrePacket.h"

class Actor;
class PathFind;
class Player;

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
    void Actor_PushBackDelete(Actor* actor);
    void PrintActorList();

    void ConnectPlayer(Player* player,int idx);

    int NumOfConnectPlayer() { return NumOfPlayer; }

public:
    std::vector<Actor*> w_Wait_AddActors;
    std::vector<Actor*> w_ActorList;
    std::vector<Actor*> w_Wait_DeleteActors;
    PathFind* mPath;


public:
    int NumOfPlayer = 0;


    bool IsAddActors = false;
    bool IsDeleteActors = false;

    int UnitIdx = 0;
};


Actor* DeathActor(ax::Node* parent, Actor* dActor);

// 시스템 엑터
Actor* SpawnCursor(ax::Node* parent);


// 유닛 엑터(건물 및 캐릭터)
Actor* SpawnSCV(ax::Node* parent, PK_Data data);
Actor* SpawnMarine(ax::Node* parent, PK_Data data);
Actor* SpawnCommandCenter(ax::Node* parent, PK_Data data);

Actor* SpawnCommandCenterComplete(ax::Node* parent, PK_Data data);

Actor* SpawnAcademy(ax::Node* parent, PK_Data data);
Actor* SpawnArmory(ax::Node* parent, PK_Data data);
Actor* SpawnBarrack(ax::Node* parent, PK_Data data);
Actor* SpawnBunker(ax::Node* parent, PK_Data data);
Actor* SpawnEngineeringBay(ax::Node* parent, PK_Data data);
Actor* SpawnSupplyDepot(ax::Node* parent, PK_Data data);
Actor* SpawnStarPort(ax::Node* parent, PK_Data data);
Actor* SpawnFactory(ax::Node* parent, PK_Data data);
Actor* SpawnScienceFacility(ax::Node* parent, PK_Data data);
Actor* SpawnRefinery(ax::Node* parent, PK_Data data);



// 리소스 액터 생성
Actor* SpawnMineral(ax::Node* parent, PK_Data data);
Actor* SpawnMineral(ax::Node* Parent);

Actor* SpawnGas(ax::Node* parent, PK_Data data);
Actor* SpawnGas(ax::Node* parent);

// 건물 설치할때 블루프린트 스폰하기

Actor* BPAcademy(ax::Node* parent);
Actor* BPArmory(ax::Node* parent);
Actor* BPBarrack(ax::Node* parent);
Actor* BPBunker(ax::Node* parent);
Actor* BPCommandCenter(ax::Node* parent);
Actor* BPEngineeringBay(ax::Node* parent);
Actor* BPStarPort(ax::Node* parent);
Actor* BPSupplyDepot(ax::Node* parent);
Actor* BPFactory(ax::Node* parent);
Actor* BPScienceFacility(ax::Node* parent);
Actor* BPRefinery(ax::Node* parent);



