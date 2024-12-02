#pragma once
#include "PreDefines.h"



enum class ECharDir
{
    Left = 0,
    Right,
    Face,
    Back,



    Dir_Count,
};

enum class ECharName
{
    None = 0,
    ///////
    // 아래에 이미지 추가할때마다 추가하기
    Farmer,
    Select,


    ///////
    Name_Count,
};

enum class ECharAct
{
    Idle = 0,
    Move,
    //////////
    // 행동들 추가하기









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
