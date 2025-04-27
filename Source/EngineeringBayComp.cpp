#include "pch.h"
#include "Actor.h"
#include "EngineeringBayComp.h"
#include "DrawComp.h"

EngineeringBayComp::EngineeringBayComp(Actor* actor) : UnitComp(actor)
{}

EngineeringBayComp::~EngineeringBayComp() {}

void EngineeringBayComp::MessageProc(ActorMessage& msg) {}

void EngineeringBayComp::update(float delta) {}
