#pragma once
#include "IActorComp.h"
#include "Goal/Base/Goal.h"
#include "Goal/Base/Goal_Think.h"

class GoalComp : public IActorComp
{
public:
    const static std::string COMPONENT_NAME;

    GoalComp(Actor* actor);
    ~GoalComp();

    virtual void update(float delta) override;


public:
    Goal_Think* mThink = nullptr;

    GoalType mCurGoal;
};




void AddGoal_MoveToPath(Actor* actor, ax::Vec2 dest);
void PushGoal_MoveToPath(Actor* actor, ax::Vec2 dest);

void AddGoal_BuildStructure(Actor* actor, ActorType type);
void PushGoal_BuildStructure(Actor* actor, ActorType type);

void AddGoal_MoveAndBuild(Actor* actor, ax::Vec2 dest, ActorType type);
void PushGoal_MoveAndBuild(Actor* actor, ax::Vec2 dest, ActorType type);

void AddGoal_DoingBuild(Actor* Builder, Actor* structure);
void PushGoal_DoingBuild(Actor* Builder, Actor* structure);

void AddGoal_MoveAndContinueBuild(Actor* Builder, Actor* structure);
void PushGoal_MoveAndContinueBuild(Actor* Builder, Actor* structure);

void AddGoal_MoveAndGathering(Actor* Gather, Actor* mMineral);
void PushGoal_MoveAndGathering(Actor* Gather, Actor* mMineral);

void AddGoal_AllCancel(Actor* actor);
void PushGoal_AllCancel(Actor* actor);

void AddGoal_SetTargetAndAttack(Actor* Attacker, Actor* Target);
void PushGoal_SetTargetAndAttack(Actor* Attacker, Actor* Target);

void AddGoal_ApproachToTarget(Actor* Attacker, ax::Vec2 dest);
void PushGoal_ApproachToTarget(Actor* Attacker, ax::Vec2 dest);

void AddGoal_MoveAndAttack(Actor* Attacker, Actor* Target);
void PushGoal_MoveAndAttack(Actor* Attacker, Actor* Target);


void AddGoal_ReturnCargo(Actor* Gather, Actor* Cargo);
void PushGoal_ReturnCargo(Actor* Gather, Actor* Cargo);
