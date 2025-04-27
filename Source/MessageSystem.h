#pragma once

class UILayer;
class Actor;
class Player;

enum class MsgType
{
    MoveToTarget,
    Contacted,
    Separate,
    Damaged,
    MoveClick,
    GameClick,
    Attack,
    Demaged,

    SetTarget,

    // 건설물 생성하기
    Build,
    Do_Build,
    Build_Complete,
    IsBuild_Complete,
    Build_Cancel,
    Build_Continue,
    Build_Start,
    Build_GetBuilder,
    // 유닛생산하기
    Create_SCV,


    Cancel,
    SendInfo,
    //BP
    CreateBP,
    BPCMC,
    BPSD,
};




struct ActorMessage
{
    MsgType msgType;
    Actor* sender;

    ax::Node* bodyNode = nullptr;
    void* data = nullptr;
};

void SendActorMessage(Actor* receiver, ActorMessage msg);



enum class SMsgType
{
    None,
    //Multi Select UI
    //현재 선택된 엑터의 상태를 알려주는 UI
    //단일선택인 경우 체력 마나 쉴드 강화상태 등 모든 것을 알려주고
    //다중선택인 경우 체력만 와이어프레임으로 나타냄 
    MSUI,
    //Single Select UI
    //현재 선택된 액터의 상태를 알려주는 UI
    //단일 선택에 대한 정보를 나타냄
    SSUI,
    Create_Unit,
    

};


struct SystemMessage
{
    SMsgType smsgType = SMsgType::None;

    ActorType Atype = ActorType::None;
    ButtonType Btype = ButtonType::None;

    void* data = nullptr;
};

void SendSystemMessage(UILayer* ui, Player* player, SystemMessage smsg);
