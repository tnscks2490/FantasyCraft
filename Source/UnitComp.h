#pragma once
#include "IActorComp.h"

class Actor;

enum class UnitCommand
{
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

enum class UnitUpDown
{
    None,
    Ground,
    Sky,
};


class UnitComp : public IActorComp
{
public:
    UnitComp(Actor* actor): IActorComp(actor){}
    ~UnitComp();

    virtual void update(float delta) override;


public:
    UnitCommand mUcommand = UnitCommand::Stop;
    UnitUpDown mUUpDown = UnitUpDown::None;
};

