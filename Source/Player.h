#pragma once

class Actor;

class Player
{
public:

    Player();
    ~Player();

    void Clear();
    void Selected(Actor* actor);
    bool isSelected();

public:
    std::vector<Actor*> PlayerActors;
};

