#include "pch.h"
#include "Actor.h"
#include "DrawComp.h"
#include "BunkerComp.h"

BunkerComp::BunkerComp(Actor* actor) : UnitComp(actor)
{}

BunkerComp::~BunkerComp() {}

void BunkerComp::MessageProc(ActorMessage& msg) {}

void BunkerComp::update(float delta) {}
