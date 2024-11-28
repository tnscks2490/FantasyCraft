#pragma once

class Actor;

class Player
{
public:

    Player();
    ~Player();

    void SelectActors();

public:
    std::vector<Actor*> PlayerActors;
};

