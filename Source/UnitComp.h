#pragma once
#include "IActorComp.h"

class Actor;


enum class UnitType
{
    None = 0,
    GatheringUnit,
    BattleUnit,
    Building,
    BattleBuilding,
};


enum class UnitCommand
{
    None = 0,
    Move,           // 이동
    Stop,           // 정지
    Attack,         // 공격
    Patrol,         // 탐색( 왔다갓다)
    Hold,           // 위치사수
    Gathering,      // 채집(채광 등등 자원채취)
    ExtraSkill1,    // 특수 스킬
    ExtraSkill2,    // 특수 스킬
    ExtraSkill3,    // 특수 스킬
    ExtraSkill4,    // 특수 스킬
};

enum class UnitArea
{
    None,
    Ground,
    Sky,
};


class UnitComp : public IActorComp
{
public:
    UnitComp(Actor* actor) : IActorComp(actor) {}
    ~UnitComp();

    virtual void update(float delta) override;


    // 변경되지 않는 고유의 값
public:
    UnitArea mArea    = UnitArea::None;
    UnitType mType        = UnitType::None;


public:

    UnitCommand mCurCommand = UnitCommand::Stop;
    UnitCommand mUsingCommand[9] = {UnitCommand::None};
};

