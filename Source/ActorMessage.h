#pragma once

class Actor;
class Player;
enum class MsgType
{
    MoveToTarget,
    Contacted,
    Separate,
    Damaged,
    MoveClick,
    GameClick,
    Attack,
    Build,



    //BP
    BPCMC,
    BPSD,
};


struct ActorMessage
{
    MsgType msgType;
    Actor* sender;

    void* data = nullptr;
};

void SendActorMessage(Actor* receiver, ActorMessage msg);
