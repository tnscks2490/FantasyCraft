#pragma once

class Actor;
class Player;

struct ActorMessage
{
    enum 
    {
        MoveToTarget,
        Contacted,
        Separate,
        Damaged,
        MoveClick,
        GameClick,
        Attack,
        Build,
    } msgType;

    Actor* sender;

    void* data = nullptr;
};

void SendActorMessage(Actor* r, ActorMessage msg);
