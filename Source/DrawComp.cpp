#include "pch.h"
#include "DrawComp.h"
#include "World.h"
#include "MoveComp.h"
#include "CursorComp.h"
#include "PathFind.h"


DrawComp::DrawComp(Actor* actor)
    : IActorComp(actor)
{
    actor->mDrawComp = this;
}

DrawComp::~DrawComp()
{
    if (mRoot.isNotNull())
        mRoot->removeFromParentAndCleanup(true);

    if (mActor)
        mActor->mDrawComp = nullptr;
}

void DrawComp::update(float delta)
{
    if (mActor->mCategory == UnitCategory::Resource)
        mRoot->setLocalZOrder(129 - (int)mActor->GetPosition().y / 32);
    else
    {
        mRoot->setLocalZOrder(128 - (int)mActor->GetPosition().y / 32);
    }

    if (mActor->mActorType == ActorType::Mineral)
        return;
    if (mActor->mActorType == ActorType::Gas)
        return;


    // 커서에 한해서 변경하는 것
    if (mActor->mActorType == ActorType::Cursor)
    {
        if (mActor->mCursorComp->mState == CursorState::Idle && mCurAnimInfo->act != ECharAct::Idle)
        {
            if (mCurAnimInfo->act == ECharAct::Idle)
                return;
            ChangeAnim(ECharName::Cursor, ECharAct::Idle, ECharDir::Face);
        }
        if (mActor->mCursorComp->mState == CursorState::ContactTeam && mCurAnimInfo->act != ECharAct::OnCursorTeam)
        {
            ChangeAnim(ECharName::Cursor, ECharAct::OnCursorTeam, ECharDir::Face);
        }
        if (mActor->mCursorComp->mState == CursorState::ContactEnemy && mCurAnimInfo->act != ECharAct::OnCursorEnemy)
        {
            ChangeAnim(ECharName::Cursor, ECharAct::OnCursorEnemy, ECharDir::Face);
        }
        if (mActor->mCursorComp->mState == CursorState::Drag && mCurAnimInfo->act != ECharAct::Drag)
        {
            ChangeAnim(ECharName::Cursor, ECharAct::Drag, ECharDir::Face);
        }
        if (mActor->mCursorComp->mState == CursorState::SetAttackTarget)
        {
            ChangeAnim(ECharName::Cursor, ECharAct::Target, ECharDir::Face);
        }
    }
    else 
    {
        // 여기가 현재 애니메이션
        ECharDir dir  = mCurAnimInfo->dir;
        ECharName anim        = mCurAnimInfo->name;
        ECharAct action       = mCurAnimInfo->act;
        // 현재 행동명령
        ActionState curAction = mActor->mUnitComp->mCurAction;

        ax::Vec2 dirV;
        if (mActor->mMoveComp)
            dirV = mActor->mMoveComp->GetVelocity();

       
        if (mActionState == curAction)
        {
            if (dirV == ax::Vec2::ZERO)
            {
                if (mCurAnimInfo->dir == mCurDir)
                    return;                
            }
            else
            {
                if (mCurAnimInfo->dir == CalcAniDir(dirV))
                    return;
            }       
        } 
            



        if (dirV == ax::Vec2::ZERO && curAction != ActionState::Death)
            mCurAnimInfo->dir = mCurDir;
         

        mCurDir = CalcAniDir(dirV);

        switch (curAction)
        {
        case ActionState::Idle:
        {
            ChangeAnim(anim, ECharAct::Idle, dir);
            mActionState = curAction;   
        } break;

        case ActionState::Move:
        {
            dir        = CalcAniDir(dirV);
            ChangeAnim(anim, ECharAct::Move, dir);
            mActionState = curAction;
            if (isCarryItme)
            {
                auto node = mRoot->getChildByName("CarryMineral");
                node->setPosition(GetCarryItemPos(dir));
            }
            
        } break;

        case ActionState::Attack:
        {
            ChangeAnim(anim, ECharAct::Attack, dir,false);
            mActionState = curAction;
        } break;

        case ActionState::Death:
        {
            ChangeAnimDeath(anim);
            //ChangeAnim(anim, ECharAct::Death, ECharDir::Face, false);
            mActionState = curAction;
            mCurDir      = ECharDir::Face;
        } break;
        case ActionState::Create_Unit:
        {
            if (mCurAnimInfo->act == ECharAct::Doing)
                return;
            ChangeAnim(anim, ECharAct::Doing, ECharDir::Face);
            mActionState = curAction;
            mCurDir      = ECharDir::Face;
        } break;
        case ActionState::Gathering:
        {
            if (mCurAnimInfo->act == ECharAct::Gathering)
                return;
            ChangeAnim(anim, ECharAct::Gathering, dir, true);
            mActionState = curAction;
        }break;
        default:
            break;
        }

        mCurDir = dir;
    }
    
}

ax::Node* DrawComp::CreateRootNode()
{
    if (mRoot.isNull())
    {
        auto node = ax::Node::create();
        mRoot     = node;
        node->setName("Root");

        AddUserData();

        ///////////////////////////////
        // 루트노드 확인용 드로우 노드 //
        ///////////////////////////////
        /*auto draw = ax::DrawNode::create();
        draw->drawRect(ax::Vec2(-8, -8), ax::Vec2(8, 8), ax::Color4B::RED);
        node->addChild(draw);*/

        auto circle = ax::DrawNode::create();
        circle->drawDot(ax::Vec2::ZERO, 4, ax::Color4B::WHITE);
        node->addChild(circle);

        
        return node;
    }
    return nullptr;
}

ax::Node* DrawComp::CreatePhysicsNode(ax::Vec2 bodysize)
{
    if (mRoot.isNotNull())
    {
        //노드 생성
        auto bodyNode = ax::Node::create();
        bodyNode->setName("Body");
        
        mBodySize = bodysize;
        //피직스바디생성 및 노드에 붙여주기

        auto body = ax::PhysicsBody::createBox(bodysize);
        body->setContactTestBitmask(0xFFFFFFFF);
        body->setDynamic(false);
        bodyNode->setPhysicsBody(body);
        bodyNode->setTag(10);


        ///실제 피직스 노드의 위치를 파악하기 위한 코드
        ax::DrawNode* dNode = ax::DrawNode::create();
        dNode->drawRect((bodysize / 2) * (-1), bodysize / 2, ax::Color4B::RED);
        bodyNode->addChild(dNode);

        //루트노드에 피직스노드붙여주기
        mRoot->addChild(bodyNode);
        return bodyNode;
    }
    return nullptr;
}

ax::Node* DrawComp::CreateBPPhysicsNode(ax::Vec2 bodysize)
{
    if (mRoot.isNotNull())
    {
        auto bodyNode = ax::Node::create();
        bodyNode->setName("BPBody");
        // 피직스바디생성 및 노드에 붙여주기
        auto body = ax::PhysicsBody::createBox(bodysize);
        body->setContactTestBitmask(0xFFFFFFFF);
        body->setDynamic(false);
        bodyNode->setPhysicsBody(body);
        bodyNode->setTag(11);

        ax::DrawNode* rect = ax::DrawNode::create();
        auto color         = ax::Color4B(0, 255, 0, 100);
        rect->drawSolidRect(ax::Vec2(-bodysize.x / 2, -bodysize.y / 2), ax::Vec2(bodysize.x / 2, bodysize.y/2), color);
        rect->setName("BPBodyRect");
        bodyNode->addChild(rect);

        return bodyNode;
    }
    return nullptr;
}

ax::Node* DrawComp::Create_Small_BPPhysicsNode()
{
    ax::Vec2 bodysize(32, 32);
    if (mRoot.isNotNull())
    {
        auto mainBody = ax::Node::create();
        mainBody->setName("BPMainBody");
        mRoot->addChild(mainBody, 2.f);

        // 탐지 피직스바디
        ////////////////////////////////////////////
        auto body1 = CreateBPPhysicsNode(bodysize);
        mainBody->addChild(body1);
        body1->setPosition(ax::Vec2(-32, 16));

        auto body2 = CreateBPPhysicsNode(bodysize);
        mainBody->addChild(body2);
        body2->setPosition(ax::Vec2(0, 16));

        auto body3 = CreateBPPhysicsNode(bodysize);
        mainBody->addChild(body3);
        body3->setPosition(ax::Vec2(32, 16));

        /////////////////////////////////////////
        auto body4 = CreateBPPhysicsNode(bodysize);
        mainBody->addChild(body4);
        body4->setPosition(ax::Vec2(-32, -16));

        auto body5 = CreateBPPhysicsNode(bodysize);
        mainBody->addChild(body5);
        body5->setPosition(ax::Vec2(0, -16));

        auto body6 = CreateBPPhysicsNode(bodysize);
        mainBody->addChild(body6);
        body6->setPosition(ax::Vec2(32, -16));
        //////////////////////////////////////////////
        return mainBody;
    }
    return nullptr;
}

ax::Node* DrawComp::Create_Middle_BPPhysicsNode()
{
    ax::Vec2 bodysize(32, 32);
    if (mRoot.isNotNull())
    {
        auto mainBody = ax::Node::create();
        mainBody->setName("BPMainBody");
        mRoot->addChild(mainBody, 2.f);

        // 탐지 피직스바디
        ////////////////////////////////////////////
        auto body1 = CreateBPPhysicsNode(bodysize);
        mainBody->addChild(body1);
        body1->setPosition(ax::Vec2(-32, 16));

        auto body2 = CreateBPPhysicsNode(bodysize);
        mainBody->addChild(body2);
        body2->setPosition(ax::Vec2(0, 16));

        auto body3 = CreateBPPhysicsNode(bodysize);
        mainBody->addChild(body3);
        body3->setPosition(ax::Vec2(32, 16));

        /////////////////////////////////////////
        auto body4 = CreateBPPhysicsNode(bodysize);
        mainBody->addChild(body4);
        body4->setPosition(ax::Vec2(-32, -16));

        auto body5 = CreateBPPhysicsNode(bodysize);
        mainBody->addChild(body5);
        body5->setPosition(ax::Vec2(0, -16));

        auto body6 = CreateBPPhysicsNode(bodysize);
        mainBody->addChild(body6);
        body6->setPosition(ax::Vec2(32, -16));
        //////////////////////////////////////////////
        return mainBody;
    }
    return nullptr;
}

ax::Node* DrawComp::Create_Big_BPPhysicsNode()
{
    ax::Vec2 bodysize(32, 32);
    if (mRoot.isNotNull())
    {
        auto mainBody = ax::Node::create();
        mainBody->setName("BPMainBody");
        mRoot->addChild(mainBody,2.f);


        //탐지 피직스바디
        ////////////////////////////////////////////
        auto body1 = CreateBPPhysicsNode(bodysize);
        mainBody->addChild(body1);
        body1->setPosition(ax::Vec2(-48, 32));

        auto body2 = CreateBPPhysicsNode(bodysize);
        mainBody->addChild(body2);
        body2->setPosition(ax::Vec2(-16, 32));

        auto body3 = CreateBPPhysicsNode(bodysize);
        mainBody->addChild(body3);
        body3->setPosition(ax::Vec2(16, 32));

        auto body4 = CreateBPPhysicsNode(bodysize);
        mainBody->addChild(body4);
        body4->setPosition(ax::Vec2(48, 32));

        /////////////////////////////////////////
        auto body5 = CreateBPPhysicsNode(bodysize);
        mainBody->addChild(body5);
        body5->setPosition(ax::Vec2(-48, 0));

        auto body6 = CreateBPPhysicsNode(bodysize);
        mainBody->addChild(body6);
        body6->setPosition(ax::Vec2(-16, 0));

        auto body7 = CreateBPPhysicsNode(bodysize);
        mainBody->addChild(body7);
        body7->setPosition(ax::Vec2(16, 0));

        auto body8 = CreateBPPhysicsNode(bodysize);
        mainBody->addChild(body8);
        body8->setPosition(ax::Vec2(48, 0));

        ///////////////////////////////////////////
        auto body9 = CreateBPPhysicsNode(bodysize);
        mainBody->addChild(body9);
        body9->setPosition(ax::Vec2(-48, -32));

        auto body10 = CreateBPPhysicsNode(bodysize);
        mainBody->addChild(body10);
        body10->setPosition(ax::Vec2(-16, -32));

        auto body11 = CreateBPPhysicsNode(bodysize);
        mainBody->addChild(body11);
        body11->setPosition(ax::Vec2(16, -32));

        auto body12 = CreateBPPhysicsNode(bodysize);
        mainBody->addChild(body12);
        body12->setPosition(ax::Vec2(48, -32));
        //////////////////////////////////////////////
        return mainBody;
    }
    return nullptr;
}

ax::Node* DrawComp::Create_Refinery_BPPhysicsNode()
{
    ax::Vec2 bodysize(96, 64);
    if (mRoot.isNotNull())
    {
        auto mainBody = ax::Node::create();
        mainBody->setName("BPMainBody");
        mRoot->addChild(mainBody, 2);

        // 탐지 피직스바디
        ////////////////////////////////////////////
        auto body1 = CreateBPPhysicsNode(bodysize);
        mainBody->addChild(body1);
        body1->setPosition(ax::Vec2(0,0));
        //////////////////////////////////////////////
        return mainBody;
    }
    return nullptr;
}


ax::Node* DrawComp::CreateCursorRect(ax::Vec2 sPos,ax::Vec2 ePos)
{
    if (mRoot.isNotNull())
    {
        auto drawnode = ax::DrawNode::create();
        drawnode->drawRect(sPos, ePos, ax::Color4B::GREEN);
        drawnode->setName("GreenRect");
        mRoot->addChild(drawnode);
    }
    return nullptr;
}

void DrawComp::ChangeRectSize(ax::Vec2 ePos)
{
    if (mRoot.isNotNull())
    {
        if (mRoot->getChildByName("GreenRect"))
        {
            ax::DrawNode* dnode = (ax::DrawNode*)mRoot->getChildByName("GreenRect");
            
        }
    }
}

ax::Node* DrawComp::CreateAnimNode(ECharName name, std::string_view nodeName)
{
    if (mRoot.isNotNull())
    {
        AnimInfo& info = FindAnimInfo(name, ECharAct::Idle, ECharDir::S);
        info.CreateAnimation();

        auto node = ax::Sprite::createWithSpriteFrame(info.animation->getFrames().front()->getSpriteFrame());
        node->setName(nodeName);
        mRoot->addChild(node);

        ax::Animate* animate = ax::Animate::create(info.animation.get());

        ax::Action* action = ax::RepeatForever::create(animate);
        action->setTag(20202);
        node->runAction(action);

        if(mCurAnimInfo == nullptr) mCurAnimInfo = &info;
        return node;  
    }
    return nullptr;
}

ax::Node* DrawComp::CreateAnimNode(ECharName name, ECharAct action, ECharDir dir, std::string_view nodeName)
{
    if (mRoot.isNotNull())
    {
        AnimInfo& info = FindAnimInfo(name, action, dir);  
        info.CreateAnimation();

        auto node = ax::Sprite::createWithSpriteFrame(info.animation->getFrames().front()->getSpriteFrame());
        node->setName(nodeName);
        mRoot->addChild(node,1.f);

        ax::Animate* animate = ax::Animate::create(info.animation.get());

        ax::Action* action = ax::RepeatForever::create(animate);
        action->setTag(20202);
        node->runAction(action);

        if(mCurAnimInfo == nullptr) mCurAnimInfo = &info;
        return node;
    }
    return nullptr;
}

ax::Node* DrawComp::CreateAnimNodeByIndex(ECharName name, int idx, std::string_view nodeName)
{
    if (mRoot.isNotNull())
    {
        AnimInfo& info = FindAnimInfoByIndex(name, ECharAct::Idle, ECharDir::Face,idx);
        info.CreateAnimation();

        auto node = ax::Sprite::createWithSpriteFrame(info.animation->getFrames().front()->getSpriteFrame());
        node->setName(nodeName);
        mRoot->addChild(node);

        ax::Animate* animate = ax::Animate::create(info.animation.get());

        ax::Action* action = ax::RepeatForever::create(animate);
        action->setTag(20202);
        node->runAction(action);

       if(mCurAnimInfo == nullptr) mCurAnimInfo = &info;
        return node;
    }
    return nullptr;
}

ax::Node* DrawComp::CreateAnimNodeByIndex(ECharName name, ECharAct action, int idx, std::string_view nodeName)
{
    if (mRoot.isNotNull())
    {
        AnimInfo& info = FindAnimInfoByIndex(name, action, ECharDir::Face, idx);
        info.CreateAnimation();

        auto node = ax::Sprite::createWithSpriteFrame(info.animation->getFrames().front()->getSpriteFrame());
        node->setName(nodeName);
        mRoot->addChild(node,1);

        ax::Animate* animate = ax::Animate::create(info.animation.get());
        ax::Action* action = ax::RepeatForever::create(animate);
        action->setTag(20202);
        node->runAction(action);

        if (mCurAnimInfo == nullptr)
            mCurAnimInfo = &info;
        return node;
    }
    return nullptr;
}

ax::Node* DrawComp::CreateDeathAnim(ECharName name, std::string_view nodeName)
{

    if (mRoot.isNotNull())
    {
        AnimInfo& animInfo = FindAnimInfo(name, ECharAct::Death, ECharDir::Face);
        animInfo.CreateAnimation();

        auto node = ax::Sprite::createWithSpriteFrame(animInfo.animation->getFrames().front()->getSpriteFrame());
        node->setName(nodeName);

        mRoot->addChild(node, 1);
        node->setPosition(ax::Vec2::ZERO);

        ax::Animate* animate = ax::Animate::create(animInfo.animation.get());

        auto removeNode = ax::CallFuncN::create([mActor = this->mActor](ax::Node* sender) {
            sender->removeFromParentAndCleanup(true);
            delete mActor;
        });

        // 4. 시퀀스로 실행
        auto sequence = ax::Sequence::create(animate, removeNode, nullptr);
        sequence->setTag(20202);
        node->runAction(sequence);

        /////
        return node;
    }

    return nullptr;
}

ax::Node* DrawComp::CreateSelectedNode(ax::Vec2 bodySize)
{
    if (mRoot.isNotNull())
    {
        auto bs = bodySize;

        auto selectanim = ax::DrawNode::create();

        if (mActor->mID == TcpClient::get()->GetID())
            selectanim->drawCircle(ax::Vec2(0, -bodySize.y / 8), bodySize.y/2, 360.f, 20, false, 1.5f, 1.0f,
                                   ax::Color4B::GREEN);
        else
            selectanim->drawCircle(ax::Vec2(0, -bodySize.y / 8), bodySize.y/2, 360.f, 20, false, 1.5f, 1.0f,
                                   ax::Color4B::RED);

        selectanim->setName("Select");
        selectanim->setVisible(false);
        mRoot->addChild(selectanim, 0.9f);
        return selectanim;
    }
    return nullptr;
}

ax::Node* DrawComp::CreateHPBarByIndex(ECharName name, int idx, std::string_view nodeName)
{
    if (mRoot.isNotNull())
    {
        AnimInfo& info = FindAnimInfoByIndex(name, ECharAct::HPBar, ECharDir::Face, idx);
        info.CreateAnimation();

        auto node = ax::Sprite::createWithSpriteFrame(info.animation->getFrames().front()->getSpriteFrame());
        node->setName(nodeName);
        

        ax::Animate* animate = ax::Animate::create(info.animation.get());

        ax::Action* action = ax::RepeatForever::create(animate);
        action->setTag(20202);
        node->runAction(action);

        if (mCurAnimInfo == nullptr)
            mCurAnimInfo = &info;
        return node;
    }
    return nullptr;
}

ax::Node* DrawComp::CreateDemageNode(ActorType type)
{
    if (mRoot.isNotNull())
    {
        ECharAct animType = ECharAct::Idle;
        switch (type)
        {
        case ActorType::Marine: animType = ECharAct::MarineSpark; break;
        case ActorType::SCV: animType = ECharAct::SCVSpark; break;
        default: break;
        }


        AnimInfo& info = FindAnimInfo(ECharName::Effect, animType, ECharDir::Face);
        info.CreateAnimation();

        auto node = ax::Sprite::createWithSpriteFrame(info.animation->getFrames().front()->getSpriteFrame());
        node->setName("EffectNode");
        mRoot->addChild(node,2);

        ax::Animate* animate = ax::Animate::create(info.animation.get());
        ax::Action* action = ax::Repeat::create(animate,1);
        action->setTag(20202);


        auto removeNode = ax::CallFunc::create([node]() { node->removeFromParentAndCleanup(true); });

        // 4. 시퀀스로 실행
        auto sequence = ax::Sequence::create(animate, removeNode, nullptr);
        node->runAction(sequence);


        return node;
    }
    return nullptr;
}

ax::Node* DrawComp::CreateGatheringNode(ActorType type)
{
    if (mRoot.isNotNull())
    {
        ECharAct animType = ECharAct::Idle;
        switch (type)
        {
        case ActorType::Marine:
            animType = ECharAct::MarineSpark;
            break;
        case ActorType::SCV:
            animType = ECharAct::SCVSpark;
            break;
        default:
            break;
        }

        AnimInfo& info = FindAnimInfo(ECharName::Effect, animType, ECharDir::Face);
        info.CreateAnimation();

        auto node = ax::Sprite::createWithSpriteFrame(info.animation->getFrames().front()->getSpriteFrame());
        node->setName("GatherAnim");

        mRoot->addChild(node,2);

        ax::Animate* animate = ax::Animate::create(info.animation.get());
        ax::Action* action   = ax::RepeatForever::create(animate);
        action->setTag(20202);
        node->runAction(action);

        return node;
    }
    return nullptr;
}

ax::Node* DrawComp::CreateCarryMineral()
{

    if (mRoot.isNotNull())
    {
        AnimInfo& info = FindAnimInfo(ECharName::CarryMineral, ECharAct::Idle, mCurDir);
        info.CreateAnimation();

        auto node = ax::Sprite::createWithSpriteFrame(info.animation->getFrames().front()->getSpriteFrame());
        node->setName("CarryMineral");
        mRoot->addChild(node);

        ax::Animate* animate = ax::Animate::create(info.animation.get());
        ax::Action* action = ax::RepeatForever::create(animate);
        action->setTag(20202);
        node->runAction(action);

        node->setPosition(GetCarryItemPos(mCurDir));
        isCarryItme = true;
        return node;
    }
    return nullptr;
}

ax::Node* DrawComp::CreateCarryGas()
{
    if (mRoot.isNotNull())
    {
        AnimInfo& info = FindAnimInfo(ECharName::TCarryGas, ECharAct::Idle, ECharDir::Face);
        info.CreateAnimation();

        auto node = ax::Sprite::createWithSpriteFrame(info.animation->getFrames().front()->getSpriteFrame());
        node->setName("CarryMineral");
        mRoot->addChild(node);

        ax::Animate* animate = ax::Animate::create(info.animation.get());
        ax::Action* action   = ax::RepeatForever::create(animate);
        action->setTag(20202);
        node->runAction(action);

        node->setPosition(GetCarryItemPos(mCurDir));
        isCarryItme = true;
        return node;
    }
    return nullptr;
}

ax::Vec2 DrawComp::GetCarryItemPos(ECharDir dir)
{
    switch (dir)
    {
    case ECharDir::N:    return ax::Vec2(0, 20);
    case ECharDir::NNE:  return ax::Vec2(17, 10);
    case ECharDir::NE:   return ax::Vec2(14, 14);
    case ECharDir::ENE:  return ax::Vec2(10, 17);
    case ECharDir::E:    return ax::Vec2(20, 0);
    case ECharDir::ESE:  return ax::Vec2(17, -10);
    case ECharDir::SE:   return ax::Vec2(14, -14);
    case ECharDir::SSE:  return ax::Vec2(10, -17);
    case ECharDir::S:    return ax::Vec2(0, -20);   
    case ECharDir::SSW:  return ax::Vec2(-17, -10);
    case ECharDir::SW:   return ax::Vec2(-14, -14);
    case ECharDir::WSW:  return ax::Vec2(-10, -17);
    case ECharDir::W:    return ax::Vec2(-20, 0);
    case ECharDir::WNW:  return ax::Vec2(-17, 10);
    case ECharDir::NW:   return ax::Vec2(-14, 14);
    case ECharDir::NNW:  return ax::Vec2(-10, 17);
    default:
        break;
    }
    return ax::Vec2();
}

void DrawComp::RemoveCarryItem()
{
    if (mRoot.isNotNull())
    {

        auto node = mRoot->getChildByName("CarryMineral");
        if (node != nullptr)
        {
            node->removeFromParentAndCleanup(true);
            isCarryItme = false;
        }
    }
}

void DrawComp::RemoveGatherAnim()
{
    if (mRoot.isNotNull())
    {
        auto node = mRoot->getChildByName("GatherAnim");
        node->removeFromParentAndCleanup(true);
    }
}



void DrawComp::AddUserData()
{
    if (mRoot.isNotNull())
    {
        UserData* mUserData = new UserData;
        mUserData->mActor   = mActor;
        mRoot->setUserData(mUserData);
    }
}


void DrawComp::ChangeAnim(ECharName Name, ECharAct act, ECharDir dir, bool repeat)
{
    auto animNode = mRoot->getChildByName("Anim");
    animNode->stopActionByTag(20202);

    AnimInfo& animInfo = FindAnimInfo(Name, act, dir);
    animInfo.CreateAnimation();

    ax::Animate* animate = ax::Animate::create(animInfo.animation.get());
    ax::Action* action;

    if (repeat) { action = ax::RepeatForever::create(animate);}
    else { action = ax::Repeat::create(animate,1);}

    action->setTag(20202);
    animNode->runAction(action);
    mCurAnimInfo = &animInfo;
}

void DrawComp::ChangeAnimDeath(ECharName Name)
{
    auto animNode = mRoot->getChildByName("Anim");
    animNode->stopActionByTag(20202);

    AnimInfo& animInfo = FindAnimInfo(Name, ECharAct::Death, ECharDir::Face);
    animInfo.CreateAnimation();

    ax::Animate* animate = ax::Animate::create(animInfo.animation.get());

   auto removeNode = ax::CallFuncN::create([mActor = this->mActor](ax::Node* sender) {
        sender->removeFromParentAndCleanup(true);
        //World::get()->mPath->ClrTileActorPhysics(mActor->GetPosition(), ax::Vec2(32, 32));
        //World::get()->Actor_PushBackDelete(mActor);
    });

    // 4. 시퀀스로 실행
    auto sequence = ax::Sequence::create(animate, removeNode, nullptr);
    sequence->setTag(20202);
    animNode->runAction(sequence);

    /////
    mCurAnimInfo = &animInfo;
}

void DrawComp::ChangeAnimByIndex(ECharName Name, ECharAct act, ECharDir dir, int idx)
{
    auto animNode = mRoot->getChildByName("Anim");
    animNode->stopActionByTag(20202);

    AnimInfo& animInfo = FindAnimInfoByIndex(Name, act, dir,idx);
    animInfo.CreateAnimation();

    ax::Animate* animate = ax::Animate::create(animInfo.animation.get());

    ax::Action* action;
    action = ax::RepeatForever::create(animate);
    action->setTag(20202);
    animNode->runAction(action);
}

void DrawComp::ChangeHpBarByIndex(ECharName Name, int idx)
{
    auto animNode = mRoot->getChildByName("Select")->getChildByName("HpBar");
    animNode->stopActionByTag(20202);

    AnimInfo& animInfo = FindAnimInfoByIndex(Name, ECharAct::HPBar, ECharDir::Face, idx);
    animInfo.CreateAnimation();

    ax::Animate* animate = ax::Animate::create(animInfo.animation.get());

    ax::Action* action;
    action = ax::RepeatForever::create(animate);
    action->setTag(20202);
    animNode->runAction(action);
}

void DrawComp::ChangePhysicsNodeTag(int tagNum)
{
    if (mRoot.isNotNull())
    {
        auto pbody = mRoot->getChildByName("Body");
        pbody->setTag(tagNum);
    }
}


ECharDir DrawComp::CalcAniDir(ax::Vec2 mVelocity)
{

    float cos45 = cos(AX_DEGREES_TO_RADIANS(45));
    float x     = 22.5;
    float a     = 11.25;
    if (mVelocity.y >= 0)
    {
        if (mVelocity.x > cos(AX_DEGREES_TO_RADIANS(a)))
            return ECharDir::E;
        if (mVelocity.x > cos(AX_DEGREES_TO_RADIANS(a+x)))
            return ECharDir::ENE;
        if (mVelocity.x > cos(AX_DEGREES_TO_RADIANS(a+(x*2))))
            return ECharDir::NE;
        if (mVelocity.x > cos(AX_DEGREES_TO_RADIANS(a+(x*3))))
            return ECharDir::NNE;
        if (mVelocity.x > cos(AX_DEGREES_TO_RADIANS(a+(x*4))))
            return ECharDir::N;
        if (mVelocity.x > cos(AX_DEGREES_TO_RADIANS(a+(x*5))))
            return ECharDir::NNW;
        if (mVelocity.x > cos(AX_DEGREES_TO_RADIANS(a+(x*6))))
            return ECharDir::NW;
        if (mVelocity.x > cos(AX_DEGREES_TO_RADIANS(a+(x*7))))
            return ECharDir::WNW;
        
        return ECharDir::W;
    }
    else
    {
        x *= -1;
        if (mVelocity.x > cos(AX_DEGREES_TO_RADIANS(a +(x*1))))
            return ECharDir::E;
        if (mVelocity.x > cos(AX_DEGREES_TO_RADIANS(a + (x * 2))))
            return ECharDir::ESE;
        if (mVelocity.x > cos(AX_DEGREES_TO_RADIANS(a + (x * 3))))
            return ECharDir::SE;
        if (mVelocity.x > cos(AX_DEGREES_TO_RADIANS(a + (x * 4))))
            return ECharDir::SSE;
        if (mVelocity.x > cos(AX_DEGREES_TO_RADIANS(a + (x * 5))))
            return ECharDir::S;
        if (mVelocity.x > cos(AX_DEGREES_TO_RADIANS(a + (x * 6))))
            return ECharDir::SSW;
        if (mVelocity.x > cos(AX_DEGREES_TO_RADIANS(a + (x * 7))))
            return ECharDir::SW;
        if (mVelocity.x > cos(AX_DEGREES_TO_RADIANS(a + (x * 8))))
            return ECharDir::WSW;

        return ECharDir::W;
    }
    return ECharDir::S;
}

void DrawComp::ChangeCurDir(ax::Vec2 mTargetDir)
{
    mCurAnimInfo->dir = mActor->mDrawComp->CalcAniDir(mTargetDir / mTargetDir.length());
}

void DrawComp::isSelected()
{
    if (selected)
    {
        auto selectNode = (ax::DrawNode*)mRoot->getChildByName("Select");
        selectNode->setVisible(true);  
    }
    else
    {
        auto selectNode = (ax::DrawNode*)mRoot->getChildByName("Select");
        selectNode->setVisible(false);
    }
}

