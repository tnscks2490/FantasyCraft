#include "pch.h"
#include "Player.h"
#include "Actor.h"
#include "DrawComp.h"
#include "PlayerController.h"

Player::Player()
{
    mPC = new PlayerController(this);
}

Player::~Player() {}

void Player::Clear()
{
    for (auto ac : PlayerActors)
    {
        if (ac)
        {
            ac->mDrawComp->selected = false;         
            ac->mDrawComp->isSelected();
            ac = nullptr;
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
            actor->mDrawComp->selected = true;
            actor->mDrawComp->isSelected();
            return;
        }
    }
    actor->mDrawComp->selected = true;
    actor->mDrawComp->isSelected();
    PlayerActors.push_back(actor);

}

bool Player::isSelected()
{
    if (PlayerActors.size() > 0)
        return true;
    else
        return false;
}

void Player::PrintSelectActors()
{
    int i = 0;
    for (auto ac : PlayerActors)
    {
        if (ac)
        {
            i++;
        }
    }

    printf("현재 선택된 엑터의 수 : %d \n", i);
}
