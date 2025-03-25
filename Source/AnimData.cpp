#include "pch.h"
#include "AnimInfo.h"

using namespace ax;

AnimInfo g_AnimInfo_Marin_Move[] = {
    {ECharName::Marine, ECharAct::Move, ECharDir::N, "Plist/Marine.plist", "Marine/Move/1/%04d.png", 1, 9, (0.9f / 9), Vec2(0.5, 0.5), nullptr},
    {ECharName::Marine, ECharAct::Move, ECharDir::NNE, "Plist/Marine.plist", "Marine/Move/2/%04d.png", 1, 9, (0.9f / 9),    Vec2(0.5, 0.5), nullptr},
    {ECharName::Marine, ECharAct::Move, ECharDir::NE, "Plist/Marine.plist", "Marine/Move/3/%04d.png", 1, 9, (0.9f / 9),     Vec2(0.5, 0.5), nullptr},
    {ECharName::Marine, ECharAct::Move, ECharDir::ENE, "Plist/Marine.plist", "Marine/Move/4/%04d.png", 1, 9, (0.9f / 9),     Vec2(0.5, 0.5), nullptr},
    {ECharName::Marine, ECharAct::Move, ECharDir::E, "Plist/Marine.plist", "Marine/Move/5/%04d.png", 1, 9, (0.9f / 9),     Vec2(0.5, 0.5), nullptr},
    {ECharName::Marine, ECharAct::Move, ECharDir::ESE, "Plist/Marine.plist", "Marine/Move/6/%04d.png", 1, 9, (0.9f / 9),     Vec2(0.5, 0.5), nullptr},
    {ECharName::Marine, ECharAct::Move, ECharDir::SE, "Plist/Marine.plist", "Marine/Move/7/%04d.png", 1, 9, (0.9f / 9),     Vec2(0.5, 0.5), nullptr},
    {ECharName::Marine, ECharAct::Move, ECharDir::SSE, "Plist/Marine.plist", "Marine/Move/8/%04d.png", 1, 9, (0.9f / 9),     Vec2(0.5, 0.5), nullptr},
    {ECharName::Marine, ECharAct::Move, ECharDir::S, "Plist/Marine.plist", "Marine/Move/9/%04d.png", 1, 9, (0.9f / 9),     Vec2(0.5, 0.5), nullptr},
    {ECharName::Marine, ECharAct::Move, ECharDir::SSW, "Plist/Marine.plist", "Marine/Move/10/%04d.png", 1, 9, (0.9f / 9),     Vec2(0.5, 0.5), nullptr},
    {ECharName::Marine, ECharAct::Move, ECharDir::SW, "Plist/Marine.plist", "Marine/Move/11/%04d.png", 1, 9, (0.9f / 9),     Vec2(0.5, 0.5), nullptr},
    {ECharName::Marine, ECharAct::Move, ECharDir::WSW, "Plist/Marine.plist", "Marine/Move/12/%04d.png", 1, 9, (0.9f / 9),     Vec2(0.5, 0.5), nullptr},
    {ECharName::Marine, ECharAct::Move, ECharDir::W, "Plist/Marine.plist", "Marine/Move/13/%04d.png", 1, 9, (0.9f / 9),     Vec2(0.5, 0.5), nullptr},
    {ECharName::Marine, ECharAct::Move, ECharDir::WNW, "Plist/Marine.plist", "Marine/Move/14/%04d.png", 1, 9, (0.9f / 9),     Vec2(0.5, 0.5), nullptr},
    {ECharName::Marine, ECharAct::Move, ECharDir::NW, "Plist/Marine.plist", "Marine/Move/15/%04d.png", 1, 9, (0.9f / 9),    Vec2(0.5, 0.5), nullptr},
    {ECharName::Marine, ECharAct::Move, ECharDir::NNW, "Plist/Marine.plist", "Marine/Move/16/%04d.png", 1, 9, (0.9f / 9),     Vec2(0.5, 0.5), nullptr},
};
AnimInfo g_AnimInfo_Marin_Idle[] = {
        {ECharName::Marine, ECharAct::Idle, ECharDir::N, "Plist/Marine.plist", "Marine/Idle/1/%04d.png", 1, 5,(1.f / 5), Vec2(0.5, 0.5), nullptr},
        {ECharName::Marine, ECharAct::Idle, ECharDir::NNE, "Plist/Marine.plist", "Marine/Idle/2/%04d.png", 1, 5,(1.f / 5), Vec2(0.5, 0.5), nullptr},
        {ECharName::Marine, ECharAct::Idle, ECharDir::NE, "Plist/Marine.plist", "Marine/Idle/3/%04d.png", 1, 5, (1.f / 5), Vec2(0.5, 0.5), nullptr},
        {ECharName::Marine, ECharAct::Idle, ECharDir::ENE, "Plist/Marine.plist", "Marine/Idle/4/%04d.png", 1, 5, (1.f / 5), Vec2(0.5, 0.5), nullptr},
        {ECharName::Marine, ECharAct::Idle, ECharDir::E, "Plist/Marine.plist", "Marine/Idle/5/%04d.png", 1, 5, (1.f / 5), Vec2(0.5, 0.5), nullptr},
        {ECharName::Marine, ECharAct::Idle, ECharDir::ESE, "Plist/Marine.plist", "Marine/Idle/6/%04d.png", 1, 5, (1.f / 5), Vec2(0.5, 0.5), nullptr},
        {ECharName::Marine, ECharAct::Idle, ECharDir::SE, "Plist/Marine.plist", "Marine/Idle/7/%04d.png", 1, 5, (1.f / 5), Vec2(0.5, 0.5), nullptr},
        {ECharName::Marine, ECharAct::Idle, ECharDir::SSE, "Plist/Marine.plist", "Marine/Idle/8/%04d.png", 1, 5, (1.f / 5), Vec2(0.5, 0.5), nullptr},
        {ECharName::Marine, ECharAct::Idle, ECharDir::S, "Plist/Marine.plist", "Marine/Idle/9/%04d.png", 1, 5, (1.f / 5), Vec2(0.5, 0.5), nullptr},
        {ECharName::Marine, ECharAct::Idle, ECharDir::SSW, "Plist/Marine.plist", "Marine/Idle/10/%04d.png", 1, 5, (1.f / 5), Vec2(0.5, 0.5), nullptr},
        {ECharName::Marine, ECharAct::Idle, ECharDir::SW, "Plist/Marine.plist", "Marine/Idle/11/%04d.png", 1, 5, (1.f / 5), Vec2(0.5, 0.5), nullptr},
        {ECharName::Marine, ECharAct::Idle, ECharDir::WSW, "Plist/Marine.plist", "Marine/Idle/12/%04d.png", 1, 5, (1.f / 5), Vec2(0.5, 0.5), nullptr},
        {ECharName::Marine, ECharAct::Idle, ECharDir::W, "Plist/Marine.plist", "Marine/Idle/13/%04d.png", 1, 5, (1.f / 5), Vec2(0.5, 0.5), nullptr},
        {ECharName::Marine, ECharAct::Idle, ECharDir::WNW, "Plist/Marine.plist", "Marine/Idle/14/%04d.png", 1, 5, (1.f / 5), Vec2(0.5, 0.5), nullptr},
        {ECharName::Marine, ECharAct::Idle, ECharDir::NW, "Plist/Marine.plist", "Marine/Idle/15/%04d.png", 1, 5, (1.f / 5), Vec2(0.5, 0.5), nullptr},
        {ECharName::Marine, ECharAct::Idle, ECharDir::NNW, "Plist/Marine.plist", "Marine/Idle/16/%04d.png", 1, 5, (1.f / 5), Vec2(0.5, 0.5), nullptr},
};
AnimInfo g_AnimInfo_Marine_Attack[] = {
        {ECharName::Marine, ECharAct::Attack, ECharDir::N, "Plist/Marine.plist", "Marine/Attack/1/%04d.png", 1, 6,(0.3f / 6), Vec2(0.5, 0.5), nullptr},
        {ECharName::Marine, ECharAct::Attack, ECharDir::NNE, "Plist/Marine.plist", "Marine/Attack/2/%04d.png", 1, 6,(0.3f / 6), Vec2(0.5, 0.5), nullptr},
        {ECharName::Marine, ECharAct::Attack, ECharDir::NE, "Plist/Marine.plist", "Marine/Attack/3/%04d.png", 1, 6, (0.3f / 6), Vec2(0.5, 0.5), nullptr},
        {ECharName::Marine, ECharAct::Attack, ECharDir::ENE, "Plist/Marine.plist", "Marine/Attack/4/%04d.png", 1, 6, (0.3f / 6), Vec2(0.5, 0.5), nullptr},
        {ECharName::Marine, ECharAct::Attack, ECharDir::E, "Plist/Marine.plist", "Marine/Attack/5/%04d.png", 1, 6, (0.3f / 6), Vec2(0.5, 0.5), nullptr},
        {ECharName::Marine, ECharAct::Attack, ECharDir::ESE, "Plist/Marine.plist", "Marine/Attack/6/%04d.png", 1, 6, (0.3f / 6), Vec2(0.5, 0.5), nullptr},
        {ECharName::Marine, ECharAct::Attack, ECharDir::SE, "Plist/Marine.plist", "Marine/Attack/7/%04d.png", 1, 6, (0.3f / 6), Vec2(0.5, 0.5), nullptr},
        {ECharName::Marine, ECharAct::Attack, ECharDir::SSE, "Plist/Marine.plist", "Marine/Attack/8/%04d.png", 1, 6, (0.3f / 6), Vec2(0.5, 0.5), nullptr},
        {ECharName::Marine, ECharAct::Attack, ECharDir::S, "Plist/Marine.plist", "Marine/Attack/9/%04d.png", 1, 6, (0.3f / 6), Vec2(0.5, 0.5), nullptr},
        {ECharName::Marine, ECharAct::Attack, ECharDir::SSW, "Plist/Marine.plist", "Marine/Attack/10/%04d.png", 1, 6, (0.3f / 6), Vec2(0.5, 0.5), nullptr},
        {ECharName::Marine, ECharAct::Attack, ECharDir::SW, "Plist/Marine.plist", "Marine/Attack/11/%04d.png", 1, 6, (0.3f / 6), Vec2(0.5, 0.5), nullptr},
        {ECharName::Marine, ECharAct::Attack, ECharDir::WSW, "Plist/Marine.plist", "Marine/Attack/12/%04d.png", 1, 6, (0.3f / 6), Vec2(0.5, 0.5), nullptr},
        {ECharName::Marine, ECharAct::Attack, ECharDir::W, "Plist/Marine.plist", "Marine/Attack/13/%04d.png", 1, 6, (0.3f / 6), Vec2(0.5, 0.5), nullptr},
        {ECharName::Marine, ECharAct::Attack, ECharDir::WNW, "Plist/Marine.plist", "Marine/Attack/14/%04d.png", 1, 6, (0.3f / 6), Vec2(0.5, 0.5), nullptr},
        {ECharName::Marine, ECharAct::Attack, ECharDir::NW, "Plist/Marine.plist", "Marine/Attack/15/%04d.png", 1, 6, (0.3f / 6), Vec2(0.5, 0.5), nullptr},
        {ECharName::Marine, ECharAct::Attack, ECharDir::NNW, "Plist/Marine.plist", "Marine/Attack/16/%04d.png", 1, 6, (0.3f / 6), Vec2(0.5, 0.5), nullptr},


};
AnimInfo g_AnimInfo_Marine_Death[] = {
        {ECharName::Marine, ECharAct::Death, ECharDir::Face, "Plist/Marine.plist", "Marine/Death/%04d.png", 1, 8, (1.f / 8), Vec2(0.5, 0.5), nullptr},

};

AnimInfo g_AnimInfo_SCV_Idle[] = {
    {ECharName::SCV, ECharAct::Idle, ECharDir::N, "Plist/SCV.plist", "SCV/Idle/1/0001.png", 1, 1, (1.f / 1), Vec2(0.5, 0.5), nullptr},
    {ECharName::SCV, ECharAct::Idle, ECharDir::NNE, "Plist/SCV.plist", "SCV/Idle/2/0001.png", 1, 1, (1.f / 1),     Vec2(0.5, 0.5), nullptr},
    {ECharName::SCV, ECharAct::Idle, ECharDir::NE, "Plist/SCV.plist", "SCV/Idle/3/0001.png", 1, 1, (1.f / 1),     Vec2(0.5, 0.5), nullptr},
    {ECharName::SCV, ECharAct::Idle, ECharDir::ENE, "Plist/SCV.plist", "SCV/Idle/4/0001.png", 1, 1, (1.f / 1),     Vec2(0.5, 0.5), nullptr},
    {ECharName::SCV, ECharAct::Idle, ECharDir::E, "Plist/SCV.plist", "SCV/Idle/5/0001.png", 1, 1, (1.f / 1),     Vec2(0.5, 0.5), nullptr},
    {ECharName::SCV, ECharAct::Idle, ECharDir::ESE, "Plist/SCV.plist", "SCV/Idle/6/0001.png", 1, 1, (1.f / 1),     Vec2(0.5, 0.5), nullptr},
    {ECharName::SCV, ECharAct::Idle, ECharDir::SE, "Plist/SCV.plist", "SCV/Idle/7/0001.png", 1, 1, (1.f / 1),     Vec2(0.5, 0.5), nullptr},
    {ECharName::SCV, ECharAct::Idle, ECharDir::SSE, "Plist/SCV.plist", "SCV/Idle/8/0001.png", 1, 1, (1.f / 1),     Vec2(0.5, 0.5), nullptr},
    {ECharName::SCV, ECharAct::Idle, ECharDir::S, "Plist/SCV.plist", "SCV/Idle/9/0001.png", 1, 1, (1.f / 1),     Vec2(0.5, 0.5), nullptr},
    {ECharName::SCV, ECharAct::Idle, ECharDir::SSW, "Plist/SCV.plist", "SCV/Idle/10/0001.png", 1, 1, (1.f / 1),     Vec2(0.5, 0.5), nullptr},
    {ECharName::SCV, ECharAct::Idle, ECharDir::SW, "Plist/SCV.plist", "SCV/Idle/11/0001.png", 1, 1, (1.f / 1),     Vec2(0.5, 0.5), nullptr},
    {ECharName::SCV, ECharAct::Idle, ECharDir::WSW, "Plist/SCV.plist", "SCV/Idle/12/0001.png", 1, 1, (1.f / 1),     Vec2(0.5, 0.5), nullptr},
    {ECharName::SCV, ECharAct::Idle, ECharDir::W, "Plist/SCV.plist", "SCV/Idle/13/0001.png", 1, 1, (1.f / 1),     Vec2(0.5, 0.5), nullptr},
    {ECharName::SCV, ECharAct::Idle, ECharDir::WNW, "Plist/SCV.plist", "SCV/Idle/14/0001.png", 1, 1, (1.f / 1),     Vec2(0.5, 0.5), nullptr},
    {ECharName::SCV, ECharAct::Idle, ECharDir::NW, "Plist/SCV.plist", "SCV/Idle/15/0001.png", 1, 1, (1.f / 1),     Vec2(0.5, 0.5), nullptr},
    {ECharName::SCV, ECharAct::Idle, ECharDir::NNW, "Plist/SCV.plist", "SCV/Idle/16/0001.png", 1, 1, (1.f / 1),     Vec2(0.5, 0.5), nullptr},
};
AnimInfo g_AnimInfo_SCV_Move[] = {
    {ECharName::SCV, ECharAct::Move, ECharDir::N, "Plist/SCV.plist", "SCV/Move/1/0001.png", 1, 1, (1.f / 1),     Vec2(0.5, 0.5), nullptr},
    {ECharName::SCV, ECharAct::Move, ECharDir::NNE, "Plist/SCV.plist", "SCV/Move/2/0001.png", 1, 1, (1.f / 1),     Vec2(0.5, 0.5), nullptr},
    {ECharName::SCV, ECharAct::Move, ECharDir::NE, "Plist/SCV.plist", "SCV/Move/3/0001.png", 1, 1, (1.f / 1),     Vec2(0.5, 0.5), nullptr},
    {ECharName::SCV, ECharAct::Move, ECharDir::ENE, "Plist/SCV.plist", "SCV/Move/4/0001.png", 1, 1, (1.f / 1),     Vec2(0.5, 0.5), nullptr},
    {ECharName::SCV, ECharAct::Move, ECharDir::E, "Plist/SCV.plist", "SCV/Move/5/0001.png", 1, 1, (1.f / 1),     Vec2(0.5, 0.5), nullptr},
    {ECharName::SCV, ECharAct::Move, ECharDir::ESE, "Plist/SCV.plist", "SCV/Move/6/0001.png", 1, 1, (1.f / 1),     Vec2(0.5, 0.5), nullptr},
    {ECharName::SCV, ECharAct::Move, ECharDir::SE, "Plist/SCV.plist", "SCV/Move/7/0001.png", 1, 1, (1.f / 1),     Vec2(0.5, 0.5), nullptr},
    {ECharName::SCV, ECharAct::Move, ECharDir::SSE, "Plist/SCV.plist", "SCV/Move/8/0001.png", 1, 1, (1.f / 1),     Vec2(0.5, 0.5), nullptr},
    {ECharName::SCV, ECharAct::Move, ECharDir::S, "Plist/SCV.plist", "SCV/Move/9/0001.png", 1, 1, (1.f / 1),     Vec2(0.5, 0.5), nullptr},
    {ECharName::SCV, ECharAct::Move, ECharDir::SSW, "Plist/SCV.plist", "SCV/Move/10/0001.png", 1, 1, (1.f / 1),     Vec2(0.5, 0.5), nullptr},
    {ECharName::SCV, ECharAct::Move, ECharDir::SW, "Plist/SCV.plist", "SCV/Move/11/0001.png", 1, 1, (1.f / 1),     Vec2(0.5, 0.5), nullptr},
    {ECharName::SCV, ECharAct::Move, ECharDir::WSW, "Plist/SCV.plist", "SCV/Move/12/0001.png", 1, 1, (1.f / 1),     Vec2(0.5, 0.5), nullptr},
    {ECharName::SCV, ECharAct::Move, ECharDir::W, "Plist/SCV.plist", "SCV/Move/13/0001.png", 1, 1, (1.f / 1),     Vec2(0.5, 0.5), nullptr},
    {ECharName::SCV, ECharAct::Move, ECharDir::WNW, "Plist/SCV.plist", "SCV/Move/14/0001.png", 1, 1, (1.f / 1),     Vec2(0.5, 0.5), nullptr},
    {ECharName::SCV, ECharAct::Move, ECharDir::NW, "Plist/SCV.plist", "SCV/Move/15/0001.png", 1, 1, (1.f / 1),     Vec2(0.5, 0.5), nullptr},
    {ECharName::SCV, ECharAct::Move, ECharDir::NNW, "Plist/SCV.plist", "SCV/Move/16/0001.png", 1, 1, (1.f / 1),     Vec2(0.5, 0.5), nullptr},
};
AnimInfo g_AnimInfo_SCV_Death[] = {
    {ECharName::SCV, ECharAct::Death, ECharDir::Face, "Plist/SCV.plist", "SCV/Death/%04d.png", 1, 9, (1.f / 9), Vec2(0.5, 0.5), nullptr},
};
AnimInfo g_AnimInfo_SCV_Gathering[] = {
    {ECharName::SCV, ECharAct::Gathering, ECharDir::N, "Plist/SCV.plist", "SCV/Gathering/1/1.png", 1, 1, (1.f / 1),     Vec2(0.5, 0.5), nullptr},
    {ECharName::SCV, ECharAct::Gathering, ECharDir::NNE, "Plist/SCV.plist", "SCV/Gathering/2/2.png", 1, 1, (1.f / 1),     Vec2(0.5, 0.5), nullptr},
    {ECharName::SCV, ECharAct::Gathering, ECharDir::NE, "Plist/SCV.plist", "SCV/Gathering/3/3.png", 1, 1, (1.f / 1),     Vec2(0.5, 0.5), nullptr},
    {ECharName::SCV, ECharAct::Gathering, ECharDir::ENE, "Plist/SCV.plist", "SCV/Gathering/4/4.png", 1, 1, (1.f / 1),     Vec2(0.5, 0.5), nullptr},
    {ECharName::SCV, ECharAct::Gathering, ECharDir::E, "Plist/SCV.plist", "SCV/Gathering/5/5.png", 1, 1, (1.f / 1),     Vec2(0.5, 0.5), nullptr},
    {ECharName::SCV, ECharAct::Gathering, ECharDir::ESE, "Plist/SCV.plist", "SCV/Gathering/6/6.png", 1, 1, (1.f / 1),     Vec2(0.5, 0.5), nullptr},
    {ECharName::SCV, ECharAct::Gathering, ECharDir::SE, "Plist/SCV.plist", "SCV/Gathering/7/7.png", 1, 1, (1.f / 1),     Vec2(0.5, 0.5), nullptr},
    {ECharName::SCV, ECharAct::Gathering, ECharDir::SSE, "Plist/SCV.plist", "SCV/Gathering/8/8.png", 1, 1, (1.f / 1),     Vec2(0.5, 0.5), nullptr},
    {ECharName::SCV, ECharAct::Gathering, ECharDir::S, "Plist/SCV.plist", "SCV/Gathering/9/9.png", 1, 1, (1.f / 1),     Vec2(0.5, 0.5), nullptr},
    {ECharName::SCV, ECharAct::Gathering, ECharDir::SSW, "Plist/SCV.plist", "SCV/Gathering/10/10.png", 1, 1, (1.f / 1),     Vec2(0.5, 0.5), nullptr},
    {ECharName::SCV, ECharAct::Gathering, ECharDir::SW, "Plist/SCV.plist", "SCV/Gathering/11/11.png", 1, 1, (1.f / 1),     Vec2(0.5, 0.5), nullptr},
    {ECharName::SCV, ECharAct::Gathering, ECharDir::WSW, "Plist/SCV.plist", "SCV/Gathering/12/12.png", 1, 1, (1.f / 1),     Vec2(0.5, 0.5), nullptr},
    {ECharName::SCV, ECharAct::Gathering, ECharDir::W, "Plist/SCV.plist", "SCV/Gathering/13/13.png", 1, 1, (1.f / 1),     Vec2(0.5, 0.5), nullptr},
    {ECharName::SCV, ECharAct::Gathering, ECharDir::WNW, "Plist/SCV.plist", "SCV/Gathering/14/14.png", 1, 1, (1.f / 1),     Vec2(0.5, 0.5), nullptr},
    {ECharName::SCV, ECharAct::Gathering, ECharDir::NW, "Plist/SCV.plist", "SCV/Gathering/15/15.png", 1, 1, (1.f / 1),     Vec2(0.5, 0.5), nullptr},
    {ECharName::SCV, ECharAct::Gathering, ECharDir::NNW, "Plist/SCV.plist", "SCV/Gathering/16/16.png", 1, 1, (1.f / 1),     Vec2(0.5, 0.5), nullptr},
};


AnimInfo g_AnimInfo_Effect_SCVSpark[] = {
    {ECharName::Effect, ECharAct::SCVSpark, ECharDir::Face, "Plist/SCVSpark.plist", "SCVSpark/%04d.png", 1, 10, (0.5f / 10), Vec2(0.5, 0.5), nullptr},
};
AnimInfo g_AnimInfo_Effect_MarineSpark[] = {
    {ECharName::Effect, ECharAct::MarineSpark, ECharDir::Face, "Plist/MarineSpark.plist", "MarineSpark/%04d.png", 1, 15, (0.5f / 15), Vec2(0.5, 0.5), nullptr},
};


AnimInfo g_AnimInfo_CommandCenter_Build[] = {
        {ECharName::CommandCenter, ECharAct::Idle, ECharDir::Face, "Plist/CommandCenter.plist", "CommandCenter/Idle/01.png", 1, 1, (1.f / 1), Vec2(0.5, 0.5), nullptr},
        {ECharName::CommandCenter, ECharAct::Idle, ECharDir::Face, "Plist/CommandCenter.plist", "CommandCenter/Idle/02.png", 1, 1, (1.f / 1), Vec2(0.5, 0.5), nullptr},
        {ECharName::CommandCenter, ECharAct::Idle, ECharDir::Face, "Plist/CommandCenter.plist", "CommandCenter/Idle/03.png", 1, 1, (1.f / 1), Vec2(0.5, 0.5), nullptr},
        {ECharName::CommandCenter, ECharAct::Idle, ECharDir::Face, "Plist/CommandCenter.plist", "CommandCenter/Idle/04.png", 1, 1, (1.f / 1), Vec2(0.5, 0.5), nullptr},
        {ECharName::CommandCenter, ECharAct::Idle, ECharDir::Face, "Plist/CommandCenter.plist", "CommandCenter/Idle/05.png", 1, 1, (1.f / 1), Vec2(0.5, 0.5), nullptr},
};

AnimInfo g_AnimInfo_Cursor[] = {
    {ECharName::Cursor, ECharAct::Idle, ECharDir::Face, "Plist/Cursor.plist", "Cursor/Idle/%04d.png", 1, 5, ((1.f) / 5), Vec2(0.5f,0.5f),nullptr},
    {ECharName::Cursor, ECharAct::OnCursorTeam, ECharDir::Face, "Plist/Cursor.plist", "Cursor/OnCursorTeam/%04d.png", 1, 14, ((2.f) / 14), Vec2(0.5f, 0.5f), nullptr},
    {ECharName::Cursor, ECharAct::OnCursorEnemy, ECharDir::Face, "Plist/Cursor.plist", "Cursor/OnCursorEnemy/%04d.png", 1, 14, ((2.f) / 14), Vec2(0.5f, 0.5f), nullptr},
    {ECharName::Cursor, ECharAct::Drag, ECharDir::Face, "Plist/Cursor.plist", "Cursor/Drag/%04d.png", 1, 4, ((1.f) / 4), Vec2(0.5f, 0.5f), nullptr},
    {ECharName::Cursor, ECharAct::Target, ECharDir::Face, "Plist/Cursor.plist", "Cursor/Target/%04d.png", 1, 2, ((0.5f) / 2), Vec2(0.5f, 0.5f), nullptr},
};


AnimInfo g_AnimInfo_Actor_Select[] = {
    {ECharName::Cursor, ECharAct::Target, ECharDir::Face, "Plist/Cursor.plist", "Cursor/Target/%04d.png", 1, 2, ((1.f) / 2), Vec2(0.5f, 0.5f), nullptr},
};

// 커서 Plist 추가하기 리소스 추가하기
AnimInfo g_AnimInfo_Cursor_Idle[] = {{ECharName::Cursor, ECharAct::Idle, ECharDir::Face, "Plist/Select.plist",
                                      "Select/%04d.png", 1, 4, (1.f / 1), Vec2(0.5, 0.5), nullptr}};
AnimInfo g_AnimInfo_Cursor_Target[] = {
    {ECharName::Cursor, ECharAct::Target, ECharDir::Face, "Plist/Cursor.plist", "Cursor/Target/%04d.png", 1, 2, ((1.f) / 2), Vec2(0.5f, 0.5f), nullptr},
};
AnimInfo g_AnimInfo_Action_Icon[] = {
    {ECharName::Cursor, ECharAct::Idle, ECharDir::Face, "Plist/Select.plist","Select/%04d.png", 1, 4, (1.f / 1), Vec2(0.5, 0.5), nullptr}
};


AnimInfo& FindAnimInfo(ECharName Name, ECharAct action, ECharDir dir)
{
    switch (Name)
    {
    case ECharName::Marine:
        switch (action)
        {

        case ECharAct::Idle:
            for (int i = 0; i < 16; i++)
            {
                if (g_AnimInfo_Marin_Idle[i].dir == dir)
                    return g_AnimInfo_Marin_Idle[i];
            }

        case ECharAct::Move:
            for (int i = 0; i < 16; i++)
            {
                if (g_AnimInfo_Marin_Move[i].dir == dir)
                    return g_AnimInfo_Marin_Move[i];
            } break;

        case ECharAct::Attack:
            for (int i = 0; i < 16; i++)
            {
                if (g_AnimInfo_Marine_Attack[i].dir == dir)
                    return g_AnimInfo_Marine_Attack[i];
            } break;
        case ECharAct::Death:return g_AnimInfo_Marine_Death[0];

        }
        break;


    case ECharName::SCV:
        switch (action)
        {
        case ECharAct::Idle:
            for (int i = 0; i < 16; i++)
            {
                if (g_AnimInfo_SCV_Idle[i].dir == dir)
                    return g_AnimInfo_SCV_Idle[i];
            }
        case ECharAct::Move:
            for (int i = 0; i < 16; i++)
            {
                if (g_AnimInfo_SCV_Move[i].dir == dir)
                    return g_AnimInfo_SCV_Move[i];
            }
            break;
        case ECharAct::Gathering:
            for (int i = 0; i < 4; ++i)
            {
                if (g_AnimInfo_SCV_Gathering[i].dir == dir)
                    return g_AnimInfo_SCV_Gathering[i];
            }
            break;
        case ECharAct::Death:
            return g_AnimInfo_SCV_Death[0];

        }
        break;

    case ECharName::CommandCenter:
        switch (action)
        {
        case ECharAct::Idle:
            return g_AnimInfo_CommandCenter_Build[0];
        }
    case ECharName::Cursor:
        switch (action)
        {
        case ECharAct::Idle:
            return g_AnimInfo_Cursor[0];
        case ECharAct::OnCursorTeam:
            return g_AnimInfo_Cursor[1];
        case ECharAct::OnCursorEnemy:
            return g_AnimInfo_Cursor[2];
        case ECharAct::Drag:
            return g_AnimInfo_Cursor[3];
        case ECharAct::Target:
            return g_AnimInfo_Cursor[4];
        default:
            break;
        }
    // 여기는 이펙트의 영역
    case ECharName::Effect:
    {
        switch (action)
        {
        case ECharAct::SCVSpark:
            return g_AnimInfo_Effect_SCVSpark[0];
        case ECharAct::MarineSpark:
            return g_AnimInfo_Effect_MarineSpark[0];
        default:
            break;
        }
    }
    break;
    }

    return g_AnimInfo_Effect_SCVSpark[0];

}

AnimInfo& FindAnimInfoByIndex(ECharName name, ECharAct act, ECharDir dir, int idx)
{
    switch (name)
    {
    case ECharName::Marine:
        break;
    case ECharName::SCV:
        break;
    case ECharName::CommandCenter:
        return g_AnimInfo_CommandCenter_Build[idx];
        break;
    case ECharName::Effect:
        break;
    default:
        break;
    }
    return g_AnimInfo_Effect_SCVSpark[idx];
}
