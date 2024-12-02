#include "pch.h"
#include "Player.h"
#include "Actor.h"

Player::Player()
{

}

Player::~Player() {}

void Player::Selected(Actor* actor)
{
    for (auto ac : PlayerActors)
    {
        if (ac == nullptr)
        {
            ac = actor;
            return;
        }
    }

    PlayerActors.push_back(actor);
}

bool Player::isSelected()
{
    if (PlayerActors.size() > 0)
        return true;
    else
        return false;
}
