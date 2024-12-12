#pragma once

class IActorComponent;




    /*
  Actor간에 메세지를 전달한다.

  결국, Component간에 메세지를 전달하는 거랑 같다.

*/
struct ActorMessage
{
    enum 
    {
        MoveToTarget,
        AddToNextTarget,
        Contacted,
        Separate,
        Damaged,
        MoveClick,
        GameClick,
        Attack,



        // 상태변화가 일어날때 보내는 메세지 (주로 엑터간의 사용)
        ChangeStatus,
    }
    msgType;

    Actor* sender;
    IActorComponent* senderCmp;

    void* data = nullptr;
};

void SendActorMessage(Actor* r, ActorMessage msg);


struct AMsgData_Vec2
{
    Vec2 pos;
};
struct AMsgData_Damage
{
    int damageType;
    int damageValue;
};
