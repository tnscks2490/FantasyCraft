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

    std::list<jpspath::Coord> PathSearch(PathFind* path, ax::Vec2 targetPos);

    void SetTarget(ax::Vec2 target);
    void SetPath(PathFind* path, ax::Vec2 targetPos);
    float length(ax::Vec2 v1, ax::Vec2 v2);
    ax::Vec2 Vec2DNormalized(ax::Vec2 target);
    bool IsArrive();
    void Do_Moving();
    void CheckTargetList();
    void UpdateBodyRect();

    ax::Vec2 CalcVelocity(ax::Vec2 force);

    ax::Vec2 Separation(std::vector<Actor*>& actor);
    ax::Vec2 Alignment(std::vector<Actor*>& actors);
    ax::Vec2 Cohesion(std::vector<Actor*>& actor);
    void TagNeighbors(std::vector<Actor*> ActorList, double radius);
    bool AccumulateForce(ax::Vec2 RunningTot, ax::Vec2 ForceToAdd);


    void CollisionMove(Border other);
    bool IsContacted(Border other);
    void Avoid();

public:
    //멤버 변수

    bool IsMoving     = false;
    bool IsCollision  = false;
    bool IsPathMoving = false;
    bool mTag       = false;

    std::list<ax::Vec2> mTargetList;

    ax::Vec2 mTarget;
    ax::Vec2 mVelocity;
    ax::Vec2 mCurFrameMovement;
    ax::Vec2 mHeading;
   

    Border mBodyBorder;

public:
    //정해진 값
    float mSpeed = 100.0f;
    float mTimer = 0.f;

    double mWeightSeparation = 200.0;
    double mWeightAlignment  = 200.0;
    double mWeightCohesion   = 400.0;
    double mMaxForce         = 400;
    double mMaxSpeed = 50;
    double mMass = 1.0;  

};

