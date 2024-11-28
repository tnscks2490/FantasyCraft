#include "pch.h"
#include "AnimInfo.h"

using namespace ax;


AnimInfo g_AnimInfo_Farmer_Idle[] = {
    {ECharName::Farmer, ECharAct::Idle, ECharDir::Face, "Plist/Farmer.plist","Farmer/Idle/Face/%04d.png", 1, 6, (1.f / 6), Vec2(0.5, 0.5), nullptr},
    {ECharName::Farmer, ECharAct::Idle, ECharDir::Back, "Plist/Farmer.plist","Farmer/Idle/Back/%04d.png", 1, 6, (1.f / 6), Vec2(0.5, 0.5), nullptr},
    {ECharName::Farmer, ECharAct::Idle, ECharDir::Left, "Plist/Farmer.plist","Farmer/Idle/Left/%04d.png", 1, 6, (1.f / 6), Vec2(0.5, 0.5), nullptr},
    {ECharName::Farmer, ECharAct::Idle, ECharDir::Right, "Plist/Farmer.plist","Farmer/Idle/Right/%04d.png", 1, 6, (1.f / 6), Vec2(0.5, 0.5), nullptr},

};

AnimInfo g_AnimInfo_Farmer_Move[] = {
    {ECharName::Farmer, ECharAct::Move, ECharDir::Face, "Farmer.plist", "Farmer/Move/Face/%04d.png", 1, 6, (1.f / 6), Vec2(0.5, 0.5), nullptr},
    {ECharName::Farmer, ECharAct::Move, ECharDir::Back, "Farmer.plist", "Farmer/Move/Back/%04d.png", 1, 6, (1.f / 6), Vec2(0.5, 0.5), nullptr},
    {ECharName::Farmer, ECharAct::Move, ECharDir::Left, "Farmer.plist", "Farmer/Move/Left/%04d.png", 1, 6, (1.f / 6), Vec2(0.5, 0.5), nullptr},
    {ECharName::Farmer, ECharAct::Move, ECharDir::Right, "Farmer.plist", "Farmer/Move/Right/%04d.png", 1, 6, (1.f / 6), Vec2(0.5, 0.5), nullptr},

};
















AnimInfo& FindAnimInfo(ECharName Name, ECharAct action, ECharDir dir)
{
    switch (Name)
    {
    case ECharName::Farmer:
        switch (action)
        {
        case ECharAct::Idle:
            for (int i = 0; i < 4; ++i)
            {
                if (g_AnimInfo_Farmer_Idle[i].dir == dir)
                    return g_AnimInfo_Farmer_Idle[i];
            }
            break;
        case ECharAct::Move:
            for (int i = 0; i < 4; ++i)
            {
                if (g_AnimInfo_Farmer_Move[i].dir == dir)
                    return g_AnimInfo_Farmer_Move[i];
            }
            break;
        default:
            break;
        }
        break;
    }
}
