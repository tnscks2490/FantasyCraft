#include "pch.h"
#include "UI/UnitInfoLayer.h"
#include "UI/UILayer.h"
#include "Player.h"


bool UnitInfoLayer::init()
{
    if (!Layer::init())
    {
        return false;
    }

    scheduleUpdate();

    return true;
}

void UnitInfoLayer::MessageProc(SystemMessage smsg) {}


void UnitInfoLayer::update(float delta) {}
