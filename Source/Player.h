#pragma once

class Actor;



enum class PlayerCommand
{
    Idle,
    Move,
    Stop,
    Attack,
    Patrol,
    Hold,
    ExtraCommand1,
    ExtraCommand2,
    ExtraCommand3,
    ExtraCommand4,
};

class Player
{
public:

    Player();
    ~Player();

    void Clear();
    void Selected(Actor* actor);
    bool isSelected();

    PlayerCommand mCommand = PlayerCommand::Idle;

public:
    std::vector<Actor*> PlayerActors;
};

