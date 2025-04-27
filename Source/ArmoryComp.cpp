#include "pch.h"
#include "Actor.h"
#include "ArmoryComp.h"
#include "DrawComp.h"

ArmoryComp::ArmoryComp(Actor* actor):UnitComp(actor) {}

ArmoryComp::~ArmoryComp() {}

void ArmoryComp::MessageProc(ActorMessage& msg) {}

void ArmoryComp::update(float delta) {}
