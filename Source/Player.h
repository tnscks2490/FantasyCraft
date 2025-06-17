#pragma once
#include "Actor.h"
#include "ButtonInfo.h"
#include "MessageSystem.h"
#include "PlayerEventSystem.h"

class Actor;
class SelectManager;
class UILayer;

enum class PlayerRace
{
    None,
    Terran,
    Protoss,
    Zerg,
};

enum class PlayerCommand
{
    // 공용 명령
    None,
    Move,
    Stop,
    Attack,
    Patrol,
    Hold,
    Cancel,
    SetRallyPoint,
    Repair,
    Gather,

    // 테란 명령
    //CommandCenter
    Build_SCV,

    //SCV
    Build_Structure,
    Build_Advance_Structure,
    //SCV Structure,
    Build_Command_Center,
    Build_Supply_Depot,
    Build_Refinery,
    Build_Barracks,
    Build_Engineering_Bay,
    Build_Missile_Turret,
    Build_Academy,
    Build_Bunker,
    //SCV Advence Structure,
    Build_Factory,
    Build_Starport,
    Build_Science_Facility,
    Build_Armory,

    
    Liftoff,
};


enum class ActionIcon
{
    None,
    SCV,
    SCV_BuildStructure,
    SCV_BuildAdvanceStructure,
    SCV_Attack,

};



class Player
{
public:

    Player();
    ~Player();

    void MessageProc(SystemMessage smsg);
    void EvnetProc(PEvent evnet);

    void Clear();
    void Selected();
    void ClassifySelected();
    void PreSelected(Actor* actor);
    void PreClear();
    bool isSelected();
    void PrintSelectActors();
    void ReSelected();


    void PushBackActor(Actor* actor);
    void DeleteActor(Actor* actor);

    Actor* FindActor(Actor* actor);

    void MoveUnit(ax::Vec2 pos);


    void ImConnect();
    void AlertMyConnect();



    int PlayerActorsNum();
    int PrePlayerActorsNum();
    void PlayerActorsClear();
    void PrePlayerActorsClear();
    void ButtonAction(ax::Object* sender);

    PlayerCommand mCommand[9];
    PlayerRace mRace       = PlayerRace::None;

    void GetResource(int m, int g) { mMineral += m; mGas +=g;}
    void UseResource(int m, int g) { mMineral -= m; mGas -=g;}

public:


    Actor* PrePlayerActors[12] = {nullptr};
    Actor* PlayerActors[12] = {nullptr};
    Actor* mMainActor = nullptr;

    std::vector<Actor*> mActors;


    SelectManager* mSM = nullptr;



    ActionIcon mCurActionICon    = ActionIcon::None;

    UILayer* ui = nullptr;
    Actor* cursor = nullptr;

    int mMineral = 50000; // 추후에 50으로 다시 돌릴것
    int mGas      = 0;
    int MaxPop   = 200;
    int mCurPop   = 0;
    int mCurMaxPop = 10;


    // upgrade 체크리스트
    int BionicAT = 0;
    int BionicDF = 0;
    int MechanicAT = 0;
    int MechanicDF = 0;
    bool MirineRange = false;
    bool StimPack    = false;
    bool OpticalFlare = false;
    bool Restoration  = false;
    bool VultureSpeed = false;
    bool SpiderMines  = false;
    bool SiegeMode    = false;
    bool GoliathRange = false;


};



