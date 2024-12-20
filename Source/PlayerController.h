#pragma once

class Actor;
class Player;

class PlayerController
{
public:

    PlayerController(Player* player);
    ~PlayerController();

    void Reset_ActionIcon();
    void SetActorIcon();


public:



    Player* mPlayer= nullptr;
};

