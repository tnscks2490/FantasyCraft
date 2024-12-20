#include "pch.h"
#include "playerController.h"
#include "Player.h"
#include "Actor.h"



PlayerController::PlayerController(Player* player)
{
    mPlayer = player;
}

PlayerController::~PlayerController() {}

void PlayerController::Reset_ActionIcon()
{

}

void PlayerController::SetActorIcon()
{
    if (!mPlayer)
    {
        AXLOG("플레이어가 없습니다");
        return;
    }

    switch (mPlayer->mCurActionICon)
    {
    case ActionIcon::SCV:
    {
        mPlayer->mCommand[0] = PlayerCommand::Move;
        mPlayer->mCommand[1] = PlayerCommand::Stop;
        mPlayer->mCommand[2] = PlayerCommand::Attack;

        mPlayer->mCommand[3] = PlayerCommand::Repair;
        mPlayer->mCommand[4] = PlayerCommand::Gather;
        mPlayer->mCommand[5] = PlayerCommand::None;

        mPlayer->mCommand[6] = PlayerCommand::Build_Structure;
        mPlayer->mCommand[7] = PlayerCommand::Build_Advance_Structure;
        mPlayer->mCommand[8] = PlayerCommand::None;

        Reset_ActionIcon();
    } break;

    case ActionIcon::SCV_BuildStructure:
    {

    } break;


    case ActionIcon::SCV_BuildAdvanceStructure:
    {

    } break;



    default:
        break;
    }
    
}
