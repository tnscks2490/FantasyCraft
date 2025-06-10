#include "pch.h"
#include "CursorComp.h"
#include "Actor.h"
#include "PrePacket.h"
#include "BPComp.h"
#include "BuildingBluePrint.h"
#include "DrawComp.h"


CursorComp::CursorComp(Actor* actor)
    : IActorComp(actor)
{
    actor->mCursorComp = this;
}

CursorComp::~CursorComp()
{
    if (cPlayer) cPlayer = nullptr;
    if (mBP) delete mBP;
}

void CursorComp::update(float delta)
{
    switch (mState)
    {
    case CursorState::Idle:
        mActor->mDrawComp->ChangeAnim(ECharName::Cursor, ECharAct::Idle, ECharDir::Face);
        break;
    case CursorState::Drag:
    {
        if (mActor->GetRoot()->getChildByName("GreenRect"))
        {
            ax::DrawNode* drawnode = (ax::DrawNode*)mActor->GetRoot()->getChildByName("GreenRect");
            drawnode->clear();
            drawnode->drawRect(sPos - drawnode->getParent()->getPosition(),
                ePos - drawnode->getParent()->getPosition(), ax::Color4B::GREEN);
        }
    } break;

    case CursorState::Move:
        break;
    case CursorState::Click:
        break;
    case CursorState::BluePrint:
        break;
    case CursorState::ContactTeam:
        break;
    case CursorState::ContactEnemy:
        break;
    case CursorState::Target:
        mActor->mDrawComp->ChangeAnim(ECharName::Cursor, ECharAct::Target, ECharDir::Face);
        break;
    default:
        break;
    }
    if (mBP)
        mBP->SetPosition(mActor->GetPosition());
}

void CursorComp::MessageProc(ActorMessage& msg)
{

    //UserData* other = (UserData*)msg.data;
    ActorType* bpType = (ActorType*)msg.data;
    switch (msg.msgType)
    {
    case MsgType::Contacted:
    {
        ContactedUnit(msg);
    } break;
    case MsgType::Separate:
    {
        SeparateUnit(msg);
    } break;
    case MsgType::CreateBP:
        CreateBuildingBP(*bpType);
        break;
    default:
        break;
    }
}

void CursorComp::CursorUp()
{

    //GetDrawNode()->clear();
    CheckNodeInDrag();
    isDraging = false;
}

void CursorComp::BPFollowCursor()
{
   /* ax::Vec2 pos;
    pos.x = mRoot->getPosition().x / 32;
    pos.y = mRoot->getPosition().y / 32;
    sp->setPosition(pos*32);*/
}

void CursorComp::CursorMove(ax::Vec2 pos)
{
    //mDrawComp->mRoot->setPosition(pos);
}


void CursorComp::LClick(ax::Vec2 pos)
{
    if (mBP)
    {

        if (mBP->mBPComp->CheckBuildPossible())
        {
            auto bp = FindBuildingBP(mBP->mBPComp->mBPType);

            if (cPlayer->mMineral >= bp.mineralCost
                && cPlayer->mGas >= bp.gasCost)
            {
                cPlayer->UseResource(bp.mineralCost, bp.gasCost);
                CreateBuildingByBP(mBP, pos);
            }
        }           
    }
    if (mState == CursorState::Move)
    {
        SendPK_Data(114, pos);
    }
    else if (mState == CursorState::Target)
    {
        /*PK_Data data;
        data.ClientID = TcpClient::get()->GetID();
        data.input    = 114;
        data.pos      = pos;
        TcpClient::get()->SendMessageToServer(data);*/
    }
}

void CursorComp::RClick(ax::Vec2 pos)
{
    if (mBP)
    {
        ReleaseBP();
    }
    else
    {
        if (cPlayer->isSelected())
        {
            
            cPlayer->MoveUnit(pos); 
        }

    }
}

void CursorComp::ContactedUnit(ActorMessage& msg)
{
    UserData* other = (UserData*)msg.data;

    if (other)
    {
        if (other->mActor->GetRoot()->getChildByName("Body"))
        {
            auto tag = other->mActor->GetRoot()->getChildByName("Body")->getTag();
            if (tag == 10 || tag == 20)
            {
                auto otherRoot = other->mActor->GetRoot();


                if (mState == CursorState::SetAttackTarget)
                {
                    return;
                }
                else if (mState == CursorState::Target)
                {
                    return;
                }
                else if (mState != CursorState::Drag)
                {
                    if (other->mActor->mActorType == ActorType::Mineral ||
                        other->mActor->mActorType == ActorType::Gas)
                    {
                        mState = CursorState::ContactTeam;
                        return;
                    }


                    if (other->mActor->mID == mActor->mID)
                        mState = CursorState::ContactTeam;
                    else
                        mState = CursorState::ContactEnemy;
                }
            }
        }
    }
    

}

void CursorComp::SeparateUnit(ActorMessage& msg)
{

    UserData* other = (UserData*)msg.data;

    if (other->mActor->mActorType != ActorType::BP)
    {
        if (other->mActor->GetRoot()->getChildByName("Body"))
        {
            auto tag = other->mActor->GetRoot()->getChildByName("Body")->getTag();
            if (tag == 10 || tag == 20)
            {
                auto otherRoot = other->mActor->GetRoot();

                if (mState != CursorState::Drag)
                {
                    mState = CursorState::Idle;
                }
            }
        }
    }

    
}
//BP 컴포넌트 만들기!

void CursorComp::CheckNodeInDrag()
{

    int sx = sPos.x / 16;
    int sy = sPos.y / 16;

    int ex = ePos.x / 16;
    int ey = ePos.y / 16;

    // 드래그 속 체크 노드
    
    auto checknode = ax::Node::create();
    checknode->setName("CursorCheckNode");
    //mDrawComp->mRoot->addChild(checknode);

    ax::Vec2 boxSize;
    boxSize.x = std::max(sPos.x, ePos.x) - std::min(sPos.x, ePos.x);
    boxSize.y = std::max(sPos.y, ePos.y) - std::min(sPos.y, ePos.y);

    auto body = ax::PhysicsBody::createBox(boxSize);
    body->setContactTestBitmask(0xFFFFFFFF);
    body->setDynamic(false);

    checknode->setPhysicsBody(body);

    // 체크노드 확인용
    auto dnode = ax::DrawNode::create();
    dnode->setName("drawCheckNode");
    dnode->setPosition(ax::Vec2(0, 0));
    checknode->addChild(dnode);
    dnode->drawRect(ax::Vec2(-boxSize.x / 2, -boxSize.y / 2), ax::Vec2(boxSize.x / 2, boxSize.y / 2),
                    ax::Color4B::BLACK);


    //위치 재조정
    ax::Vec2 nodepos;
    nodepos.x = (sPos.x - ePos.x) / 2;
    nodepos.y = (sPos.y - ePos.y) / 2;
    checknode->setPosition(nodepos);    
}

void CursorComp::DeleteCheckNode()
{
    
    //auto node = mDrawComp->mRoot->getChildByName("CursorCheckNode");

   /* if (node != nullptr)
    {
        node->getChildByName("drawCheckNode")->removeFromParent();
        node->removeFromParent();
    }*/
    
}

void CursorComp::GreenRectClear()
{
    ax::DrawNode* drawnode = (ax::DrawNode*)mActor->GetRoot()->getChildByName("GreenRect");
    drawnode->clear();
}

void CursorComp::ReleaseBP()
{
    delete mBP;
    mBP = nullptr;
}

void CursorComp::CreateBuildingBP(ActorType type)
{
    if (mBP == nullptr)
    {
        switch (type)
        {
        case ActorType::None:
            break;
        case ActorType::CommandCenter:
        {
           auto BP = BPCommandCenter(mActor->GetRoot()->getParent());
           mBP     = BP;
        }  break;
        case ActorType::Barrack:
        {
            auto BP = BPBarrack(mActor->GetRoot()->getParent());
            mBP     = BP;
        } break;
        case ActorType::Academy:
        {
            auto BP = BPAcademy(mActor->GetRoot()->getParent());
            mBP     = BP;
        }  break;
        case ActorType::Armory:
        {
            auto BP = BPArmory(mActor->GetRoot()->getParent());
            mBP     = BP;
        }break;
        case ActorType::Bunker:
        {
            auto BP = BPBunker(mActor->GetRoot()->getParent());
            mBP     = BP;
        }break;
        case ActorType::ScienceFacility:
        {
            auto BP = BPScienceFacility(mActor->GetRoot()->getParent());
            mBP     = BP;
        }
        break;
        case ActorType::SupplyDepot:
        {
            auto BP = BPSupplyDepot(mActor->GetRoot()->getParent());
            mBP     = BP;
        }
        break;
        case ActorType::Factory:
        {
            auto BP = BPFactory(mActor->GetRoot()->getParent());
            mBP     = BP;
        }
        break;
        case ActorType::Refinery:
        {
            auto BP = BPRefinery(mActor->GetRoot()->getParent());
            mBP     = BP;
        }
        break;
        case ActorType::StarPort:
        {
            auto BP = BPStarPort(mActor->GetRoot()->getParent());
            mBP     = BP;
        }
        break;
        case ActorType::EngineeringBay:
        {
            auto BP = BPEngineeringBay(mActor->GetRoot()->getParent());
            mBP     = BP;
        }
        break;
        default:
            break;
        }
    }
}

void CursorComp::CreateBuildingByBP(Actor* BP, ax::Vec2 createPos)
{
    auto pos = createPos;


    int command = 0;
    switch (BP->mBPComp->mBPType)
        {
        case ActorType::CommandCenter: command = 120;break;
        case ActorType::SupplyDepot: command = 121;break;
        case ActorType::Barrack: command = 122; break;
        case ActorType::EngineeringBay: command = 123; break;
        case ActorType::Academy: command = 124; break;
        case ActorType::Refinery: command = 125; break;
        case ActorType::Factory: command = 126; break;
        case ActorType::StarPort: command = 127; break;
        case ActorType::Armory: command = 128; break;
        case ActorType::ScienceFacility: command = 129; break;
        default:
            break;
        }

    PK_Data data;
    data.ClientID = cPlayer->mMainActor->idx;
    data.input    = command;
    data.pos      = pos;
    TcpClient::get()->SendMessageToServer(data);


    ReleaseBP();
}


