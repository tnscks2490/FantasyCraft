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
    Build,
    Do_Build,  // 건설물 생성하기
    Build_Complete,
    IsBuild_Complete,
    Build_Cancel,



    Cancel,
    SendInfo,
    //BP
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



struct SystemMessage
{
    ActorType Atype = ActorType::None;
    ButtonType Btype = ButtonType::None;

    void* data = nullptr;
};

void SendSystemMessage(UILayer* ui, Player* player, SystemMessage smsg);
