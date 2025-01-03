#pragma once
#include "Actor.h"
class Actor;
class PlayerController;

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

    void Clear();
    void Selected(Actor* actor);
    bool isSelected();
    void PrintSelectActors();

    PlayerCommand mCommand[9] = {PlayerCommand::None,};
    PlayerRace mRace       = PlayerRace::None;

public:
    std::vector<Actor*> PlayerActors;
    Actor* mMainActor;

    PlayerController* mPC = nullptr;
    ActionIcon mCurActionICon    = ActionIcon::None;


};

// 

