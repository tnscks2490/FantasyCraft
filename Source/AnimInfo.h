#pragma once
#include "PreDefines.h"



enum class ECharDir
{
    Left = 0,
    Right,
    Face,
    Back,
    N,
    NNE,
    NE,
    ENE,
    E,
    ESE,
    SE,
    SSE,
    S,
    SSW,
    SW,
    WSW,
    W,
    WNW,
    NW,
    NNW,



    Dir_Count,
};

enum class ECharName
{
    None = 0,
    ///////
    // 아래에 이미지 추가할때마다 추가하기
    Farmer,
    Select,
    Marine,
    SCV,
    CommandCenter,









    // 이펙트는 다음과 같이 정의한다.
    // ECharName == Effect
    // ECharAct == ~~의 이펙트(ex SCVSpark)
    // ECharDir == Face (기준점 항상 나옴)
    Effect,
    /////////////
    Name_Count,
};

enum class ECharAct
{
    Idle = 0,
    Move,
    Gathering,
    //////////
    // 행동들 추가하기







    //Effect 용 Action
    SCVSpark,

    //////////
    Act_Count,
};



struct AnimInfo
{
    ECharName name = ECharName::None;
    ECharAct act   = ECharAct::Idle;
    ECharDir dir   = ECharDir::Face;

    char strPlist[128];
    char format[128];

    int startFrame;
    int frameCount;
    float perFrameTime;

    ax::Vec2 anchor;
    Ptr<ax::Animation> animation;

    void CreateAnimation();

};



AnimInfo& FindAnimInfo(ECharName name, ECharAct act, ECharDir dir);
AnimInfo& FindAnimInfoByIndex(ECharName name, ECharAct act, ECharDir dir, int idx);
