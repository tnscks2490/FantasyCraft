#include "pch.h"
#include "Player.h"
#include "Actor.h"
#include "DrawComp.h"
#include "PlayerController.h"

Player::Player()
{
    mPC = new PlayerController(this);
    mCommand[0];
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

void Player::Selected()
{
    for (auto aa : PrePlayerActors)
    {
        if (aa)
        {
            for (auto ac : PlayerActors)
            {
                if (ac == nullptr)
                {
                    ac                         = aa;
                    ac->mDrawComp->selected = true;
                    ac->mDrawComp->isSelected();
                    return;
                } 
            }
            aa->mDrawComp->selected = true;
            aa->mDrawComp->isSelected();
            PlayerActors.push_back(aa);
        }      
    }   
}

void Player::PreSelected(Actor* actor)
{
    for (auto ac : PrePlayerActors)
    {
        if (ac == nullptr)
        {
            ac = actor;
            return;
        }
    }
    PrePlayerActors.push_back(actor);
}

void Player::PreClear()
{
    for (auto ac : PrePlayerActors)
    {
        if (ac){ ac = nullptr;}
    }
    PlayerActors.clear();
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

void Player::ReSelected()
{
    Clear();
    Selected();
    PrePlayerActors.clear();
}
