#pragma once

class Player;

enum class EventType
{
    None,
    GetResource,
    UseResource,
    AddPop,
    MinusPop,
};



struct PEvent
{
    EventType EType;
    int Mineral;
    int Gas;
    bool isEnough;
    Actor* sender;
    ActorType AddActorType;
};

class PlayerEventSystem
{
public:

    PlayerEventSystem();
    ~PlayerEventSystem();

    static PlayerEventSystem* get();

    void EventProc(PEvent event);
    void AddPlayer(Player* player);


public:
    PEvent mEvent;
    Player* mPlayer;
};

void SendEvent(PEvent event);
void RegistePlayer(Player* player);
