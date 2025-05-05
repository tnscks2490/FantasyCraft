#pragma once

class Actor;
class Player;

class SelectManager
{
public:

    SelectManager(Player* player);
    ~SelectManager();



public:

    Player* mPlayer= nullptr;
};

