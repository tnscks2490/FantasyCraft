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
        //각 건물마다 필요한 조건이 있다면 그걸 조건을 걸고 해당되면 지을수있게한다.
        // 내가 지은 건물들을 맵으로 저장해두고 find함수를 찾아서 사용한다.
        // 만약 있다면 조건이 충족되어 다음 건물을지을수 있게되는거고
        // 아니라면 지을수없게 해놓는다.
    } break;


    case ActionIcon::SCV_BuildAdvanceStructure:
    {

    } break;



    default:
        break;
    }
    
}
