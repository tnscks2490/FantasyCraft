#include "pch.h"
#include "PlayerEventSystem.h"


namespace
{
static PlayerEventSystem* PES = nullptr;
}

PlayerEventSystem* PlayerEventSystem::get()
{
    if (!PES)
        PES = new PlayerEventSystem;
    return PES;
}


void PlayerEventSystem::EventProc(PEvent event)
{
    mEvent = event;
    mPlayer->EvnetProc(mEvent);
}

void PlayerEventSystem::AddPlayer(Player* player)
{
    mPlayer = player;
}


PlayerEventSystem::PlayerEventSystem()
{
}

PlayerEventSystem::~PlayerEventSystem() {}


void SendEvent(PEvent event)
{
    PlayerEventSystem::get()->EventProc(event);
}

void RegistePlayer(Player* player)
{
    PlayerEventSystem::get()->AddPlayer(player);
}
