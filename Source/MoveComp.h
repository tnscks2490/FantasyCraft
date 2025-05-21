#pragma once
#include "IActorComp.h"
#include "JPSPathFinder.h"

class Actor;
class PathFind;

struct Border
{
    float left;
    float right;
    float top;
    float bottom;
};


class MoveComp : public IActorComp
{
public:
    MoveComp(Actor* actor);
    ~MoveComp();

    virtual void update(float delta) override;


    void SetTarget(ax::Vec2 target);
    void SetPath(ax::Vec2 targetPos);
    ax::Vec2 Vec2DNormalized(ax::Vec2 target);
    bool IsArrive();
    void Do_Moving();
    void CheckTargetList();
    void UpdateBodyRect();
    bool IsArriveComplete();

    void StopMove();


    ax::Vec2 CalcVelocity(ax::Vec2 force);

    ax::Vec2 Separation(std::vector<Actor*>& actor);
    ax::Vec2 Alignment(std::vector<Actor*>& actors);
    ax::Vec2 Cohesion(std::vector<Actor*>& actor);
    void TagNeighbors(std::vector<Actor*> ActorList, double radius);
    bool AccumulateForce(ax::Vec2 RunningTot, ax::Vec2 ForceToAdd);

    ax::Vec2 GetVelocity() { return mVelocity; }

    void CollisionMove(Border other);
    bool IsContacted(Border other);
    void Avoid();

    void Start_ElapsedTime() { mTimer = 0.0; }
    void Stop_ElapsedTime() { mTimer = -1.0; }


public:
    //멤버 변수

    bool IsMoving     = false;
    bool IsCollision  = false;
    bool IsPathMoving = false;
    bool mTag       = false;
    bool testing      = false;


    std::list<ax::Vec2> mTargetList;

    ax::Vec2 mTarget;
    ax::Vec2 mLastTarget;
    ax::Vec2 mVelocity;
    ax::Vec2 mCurFrameMovement;
    ax::Vec2 mHeading;
   

    Border mBodyBorder;

public:
    //정해진 값
    float mSpeed = 100.0f;
    double mTimer = -1.f;

    double mWeightSeparation = 200.0;
    double mWeightAlignment  = 200.0;
    double mWeightCohesion   = 400.0;
    double mMaxForce         = 400;
    double mMaxSpeed = 50;
    double mMass = 1.0;  


public:
    bool IsOn = true;
};

