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
    Gathering,
    SetTarget,
    GatherMineral,
    GatherGas,
    GiveResource,
    AttackTarget,
    SetAttackTarget,
    ReturnCargo,
    SearchCargo,
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

    DoOrder,



    CheckAdd_SCV,
    Add_SCV,
    Cancel_SCV,

    CheckAdd_Marine,
    Add_Marine,
    Cancel_Marine,

    CheckAdd_FireBat,
    Add_FireBat,
    Cancel_FireBat,

    CheckAdd_Medic,
    Add_Medic,
    Cancel_Medic,

    CheckAdd_Ghost,
    Add_Ghost,
    Cancel_Ghost,


    Create_Medic,
    Create_FireBat,
    Create_Ghost,
    Create_Vulture,
    Create_Tank,
    Create_Goliath,
    Create_Wraith,
    Create_Valkyrie,
    Create_DropShip,
    Create_ScienceVessel,
    Create_BattleCruiser,
    // 업그레이드 관련
    Upgrade_Bionic_AT,
    Upgrade_Bionic_DF,




    Cancel,
    SendInfo,
    //BP
    CreateBP,
    BPCMC,
    BPSD,


    // 그외

    CollisionMove,
};




struct ActorMessage
{
    MsgType msgType;
    Actor* sender;

    ax::Node* bodyNode = nullptr;
    void* data = nullptr;
};

void SendActorMessage(Actor* receiver, ActorMessage msg);


enum class ReceiverType
{
    None,
    UI,
    Player,
};


enum class SMsgType
{
    None,
    Cancel,
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
    Upgrade,
    BPCancel,
    ChangeResource,
    

};


struct SystemMessage
{
    SMsgType smsgType = SMsgType::None;
    ReceiverType recvType = ReceiverType::None;

    ActorType Atype = ActorType::None;
    ButtonType Btype = ButtonType::None;

    void* data = nullptr;
};

void SendSystemMessage(UILayer* ui, Player* player, SystemMessage smsg);

