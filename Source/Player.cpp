#include "pch.h"
#include "Player.h"
#include "Actor.h"
#include "DrawComp.h"

Player::Player()
{

}

Player::~Player() {}

void Player::Clear()
{
    for (auto ac : PlayerActors)
    {
        if (ac)
        {
            ac->mDrawComp->isSelected = false;
        }
    }
    PlayerActors.clear();
}

void Player::Selected(Actor* actor)
{
    for (auto ac : PlayerActors)
    {
        if (ac == nullptr)
        {
            ac = actor;
            actor->mDrawComp->isSelected = true;       
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
