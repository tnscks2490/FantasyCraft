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
    {ECharName::Farmer, ECharAct::Move, ECharDir::Face, "Plist/Farmer.plist", "Farmer/Move/Face/%04d.png", 1, 6, (1.f / 6), Vec2(0.5, 0.5), nullptr},
    {ECharName::Farmer, ECharAct::Move, ECharDir::Back, "Plist/Farmer.plist", "Farmer/Move/Back/%04d.png", 1, 6, (1.f / 6), Vec2(0.5, 0.5), nullptr},
    {ECharName::Farmer, ECharAct::Move, ECharDir::Left, "Plist/Farmer.plist", "Farmer/Move/Left/%04d.png", 1, 6, (1.f / 6), Vec2(0.5, 0.5), nullptr},
    {ECharName::Farmer, ECharAct::Move, ECharDir::Right, "Plist/Farmer.plist", "Farmer/Move/Right/%04d.png", 1, 6, (1.f / 6), Vec2(0.5, 0.5), nullptr},

};

AnimInfo g_AnimInfo_Marin_Move[] = {
    {ECharName::Marine, ECharAct::Move, ECharDir::N, "Plist/Marin.plist", "Marin/Move/1/%04d.png", 1, 9, (0.5f / 9), Vec2(0.5, 0.5), nullptr},
    {ECharName::Marine, ECharAct::Move, ECharDir::NNE, "Plist/Marin.plist", "Marin/Move/2/%04d.png", 1, 9, (0.5f / 9),    Vec2(0.5, 0.5), nullptr},
    {ECharName::Marine, ECharAct::Move, ECharDir::NE, "Plist/Marin.plist", "Marin/Move/3/%04d.png", 1, 9, (0.5f / 9),     Vec2(0.5, 0.5), nullptr},
    {ECharName::Marine, ECharAct::Move, ECharDir::ENE, "Plist/Marin.plist", "Marin/Move/4/%04d.png", 1, 9, (0.5f / 9),     Vec2(0.5, 0.5), nullptr},
    {ECharName::Marine, ECharAct::Move, ECharDir::E, "Plist/Marin.plist", "Marin/Move/5/%04d.png", 1, 9, (0.5f / 9),     Vec2(0.5, 0.5), nullptr},
    {ECharName::Marine, ECharAct::Move, ECharDir::ESE, "Plist/Marin.plist", "Marin/Move/6/%04d.png", 1, 9, (0.5f / 9),     Vec2(0.5, 0.5), nullptr},
    {ECharName::Marine, ECharAct::Move, ECharDir::SE, "Plist/Marin.plist", "Marin/Move/7/%04d.png", 1, 9, (0.5f / 9),     Vec2(0.5, 0.5), nullptr},
    {ECharName::Marine, ECharAct::Move, ECharDir::SSE, "Plist/Marin.plist", "Marin/Move/8/%04d.png", 1, 9, (0.5f / 9),     Vec2(0.5, 0.5), nullptr},
    {ECharName::Marine, ECharAct::Move, ECharDir::S, "Plist/Marin.plist", "Marin/Move/9/%04d.png", 1, 9, (0.5f / 9),     Vec2(0.5, 0.5), nullptr},
    {ECharName::Marine, ECharAct::Move, ECharDir::SSW, "Plist/Marin.plist", "Marin/Move/10/%04d.png", 1, 9, (0.5f / 9),     Vec2(0.5, 0.5), nullptr},
    {ECharName::Marine, ECharAct::Move, ECharDir::SW, "Plist/Marin.plist", "Marin/Move/11/%04d.png", 1, 9, (0.5f / 9),     Vec2(0.5, 0.5), nullptr},
    {ECharName::Marine, ECharAct::Move, ECharDir::WSW, "Plist/Marin.plist", "Marin/Move/12/%04d.png", 1, 9, (0.5f / 9),     Vec2(0.5, 0.5), nullptr},
    {ECharName::Marine, ECharAct::Move, ECharDir::W, "Plist/Marin.plist", "Marin/Move/13/%04d.png", 1, 9, (0.5f / 9),     Vec2(0.5, 0.5), nullptr},
    {ECharName::Marine, ECharAct::Move, ECharDir::WNW, "Plist/Marin.plist", "Marin/Move/14/%04d.png", 1, 9, (0.5f / 9),     Vec2(0.5, 0.5), nullptr},
    {ECharName::Marine, ECharAct::Move, ECharDir::NW, "Plist/Marin.plist", "Marin/Move/15/%04d.png", 1, 9, (0.5f / 9),    Vec2(0.5, 0.5), nullptr},
    {ECharName::Marine, ECharAct::Move, ECharDir::NNW, "Plist/Marin.plist", "Marin/Move/16/%04d.png", 1, 9, (0.5f / 9),     Vec2(0.5, 0.5), nullptr},
};
AnimInfo g_AnimInfo_Marin_Idle[] = {
        {ECharName::Marine, ECharAct::Idle, ECharDir::N, "Plist/Marin.plist", "Marin/Idle/1.png", 1, 1,(1.f / 1), Vec2(0.5, 0.5), nullptr},
        {ECharName::Marine, ECharAct::Idle, ECharDir::NNE, "Plist/Marin.plist", "Marin/Idle/2.png", 1, 1,(1.f / 1), Vec2(0.5, 0.5), nullptr},
        {ECharName::Marine, ECharAct::Idle, ECharDir::NE, "Plist/Marin.plist", "Marin/Idle/3.png", 1, 1, (1.f / 1), Vec2(0.5, 0.5), nullptr},
        {ECharName::Marine, ECharAct::Idle, ECharDir::ENE, "Plist/Marin.plist", "Marin/Idle/4.png", 1, 1, (1.f / 1), Vec2(0.5, 0.5), nullptr},
        {ECharName::Marine, ECharAct::Idle, ECharDir::E, "Plist/Marin.plist", "Marin/Idle/5.png", 1, 1, (1.f / 1), Vec2(0.5, 0.5), nullptr},
        {ECharName::Marine, ECharAct::Idle, ECharDir::ESE, "Plist/Marin.plist", "Marin/Idle/6.png", 1, 1, (1.f / 1), Vec2(0.5, 0.5), nullptr},
        {ECharName::Marine, ECharAct::Idle, ECharDir::SE, "Plist/Marin.plist", "Marin/Idle/7.png", 1, 1, (1.f / 1), Vec2(0.5, 0.5), nullptr},
        {ECharName::Marine, ECharAct::Idle, ECharDir::SSE, "Plist/Marin.plist", "Marin/Idle/8.png", 1, 1, (1.f / 1), Vec2(0.5, 0.5), nullptr},
        {ECharName::Marine, ECharAct::Idle, ECharDir::S, "Plist/Marin.plist", "Marin/Idle/9.png", 1, 1, (1.f / 1), Vec2(0.5, 0.5), nullptr},
        {ECharName::Marine, ECharAct::Idle, ECharDir::SSW, "Plist/Marin.plist", "Marin/Idle/10.png", 1, 1, (1.f / 1), Vec2(0.5, 0.5), nullptr},
        {ECharName::Marine, ECharAct::Idle, ECharDir::SW, "Plist/Marin.plist", "Marin/Idle/11.png", 1, 1, (1.f / 1), Vec2(0.5, 0.5), nullptr},
        {ECharName::Marine, ECharAct::Idle, ECharDir::WSW, "Plist/Marin.plist", "Marin/Idle/12.png", 1, 1, (1.f / 1), Vec2(0.5, 0.5), nullptr},
        {ECharName::Marine, ECharAct::Idle, ECharDir::W, "Plist/Marin.plist", "Marin/Idle/13.png", 1, 1, (1.f / 1), Vec2(0.5, 0.5), nullptr},
        {ECharName::Marine, ECharAct::Idle, ECharDir::WNW, "Plist/Marin.plist", "Marin/Idle/14.png", 1, 1, (1.f / 1), Vec2(0.5, 0.5), nullptr},
        {ECharName::Marine, ECharAct::Idle, ECharDir::NW, "Plist/Marin.plist", "Marin/Idle/15.png", 1, 1, (1.f / 1), Vec2(0.5, 0.5), nullptr},
        {ECharName::Marine, ECharAct::Idle, ECharDir::NNW, "Plist/Marin.plist", "Marin/Idle/16.png", 1, 1, (1.f / 1), Vec2(0.5, 0.5), nullptr},
};

AnimInfo g_AnimInfo_SCV_Idle[] = {
    {ECharName::SCV, ECharAct::Idle, ECharDir::N, "Plist/SCV.plist", "SCV/Idle/1/0001.png", 1, 1, (1.f / 1),
     Vec2(0.5, 0.5), nullptr},
    {ECharName::SCV, ECharAct::Idle, ECharDir::NNE, "Plist/SCV.plist", "SCV/Idle/2/0002.png", 1, 1, (1.f / 1),
     Vec2(0.5, 0.5), nullptr},
    {ECharName::SCV, ECharAct::Idle, ECharDir::NE, "Plist/SCV.plist", "SCV/Idle/3/0003.png", 1, 1, (1.f / 1),
     Vec2(0.5, 0.5), nullptr},
    {ECharName::SCV, ECharAct::Idle, ECharDir::ENE, "Plist/SCV.plist", "SCV/Idle/4/0004.png", 1, 1, (1.f / 1),
     Vec2(0.5, 0.5), nullptr},
    {ECharName::SCV, ECharAct::Idle, ECharDir::E, "Plist/SCV.plist", "SCV/Idle/5/0005.png", 1, 1, (1.f / 1),
     Vec2(0.5, 0.5), nullptr},
    {ECharName::SCV, ECharAct::Idle, ECharDir::ESE, "Plist/SCV.plist", "SCV/Idle/6/0006.png", 1, 1, (1.f / 1),
     Vec2(0.5, 0.5), nullptr},
    {ECharName::SCV, ECharAct::Idle, ECharDir::SE, "Plist/SCV.plist", "SCV/Idle/7/0007.png", 1, 1, (1.f / 1),
     Vec2(0.5, 0.5), nullptr},
    {ECharName::SCV, ECharAct::Idle, ECharDir::SSE, "Plist/SCV.plist", "SCV/Idle/8/0008.png", 1, 1, (1.f / 1),
     Vec2(0.5, 0.5), nullptr},
    {ECharName::SCV, ECharAct::Idle, ECharDir::S, "Plist/SCV.plist", "SCV/Idle/9/0009.png", 1, 1, (1.f / 1),
     Vec2(0.5, 0.5), nullptr},
    {ECharName::SCV, ECharAct::Idle, ECharDir::SSW, "Plist/SCV.plist", "SCV/Idle/10/0010.png", 1, 1, (1.f / 1),
     Vec2(0.5, 0.5), nullptr},
    {ECharName::SCV, ECharAct::Idle, ECharDir::SW, "Plist/SCV.plist", "SCV/Idle/11/0011.png", 1, 1, (1.f / 1),
     Vec2(0.5, 0.5), nullptr},
    {ECharName::SCV, ECharAct::Idle, ECharDir::WSW, "Plist/SCV.plist", "SCV/Idle/12/0012.png", 1, 1, (1.f / 1),
     Vec2(0.5, 0.5), nullptr},
    {ECharName::SCV, ECharAct::Idle, ECharDir::W, "Plist/SCV.plist", "SCV/Idle/13/0013.png", 1, 1, (1.f / 1),
     Vec2(0.5, 0.5), nullptr},
    {ECharName::SCV, ECharAct::Idle, ECharDir::WNW, "Plist/SCV.plist", "SCV/Idle/14/0014.png", 1, 1, (1.f / 1),
     Vec2(0.5, 0.5), nullptr},
    {ECharName::SCV, ECharAct::Idle, ECharDir::NW, "Plist/SCV.plist", "SCV/Idle/15/0015.png", 1, 1, (1.f / 1),
     Vec2(0.5, 0.5), nullptr},
    {ECharName::SCV, ECharAct::Idle, ECharDir::NNW, "Plist/SCV.plist", "SCV/Idle/16/0016.png", 1, 1, (1.f / 1),
     Vec2(0.5, 0.5), nullptr},
};
AnimInfo g_AnimInfo_SCV_Move[] = {
    {ECharName::SCV, ECharAct::Move, ECharDir::N, "Plist/SCV.plist", "SCV/Move/1/0001.png", 1, 1, (1.f / 1),     Vec2(0.5, 0.5), nullptr},
    {ECharName::SCV, ECharAct::Move, ECharDir::NNE, "Plist/SCV.plist", "SCV/Move/2/0002.png", 1, 1, (1.f / 1),     Vec2(0.5, 0.5), nullptr},
    {ECharName::SCV, ECharAct::Move, ECharDir::NE, "Plist/SCV.plist", "SCV/Move/3/0003.png", 1, 1, (1.f / 1),     Vec2(0.5, 0.5), nullptr},
    {ECharName::SCV, ECharAct::Move, ECharDir::ENE, "Plist/SCV.plist", "SCV/Move/4/0004.png", 1, 1, (1.f / 1),     Vec2(0.5, 0.5), nullptr},
    {ECharName::SCV, ECharAct::Move, ECharDir::E, "Plist/SCV.plist", "SCV/Move/5/0005.png", 1, 1, (1.f / 1),     Vec2(0.5, 0.5), nullptr},
    {ECharName::SCV, ECharAct::Move, ECharDir::ESE, "Plist/SCV.plist", "SCV/Move/6/0006.png", 1, 1, (1.f / 1),     Vec2(0.5, 0.5), nullptr},
    {ECharName::SCV, ECharAct::Move, ECharDir::SE, "Plist/SCV.plist", "SCV/Move/7/0007.png", 1, 1, (1.f / 1),     Vec2(0.5, 0.5), nullptr},
    {ECharName::SCV, ECharAct::Move, ECharDir::SSE, "Plist/SCV.plist", "SCV/Move/8/0008.png", 1, 1, (1.f / 1),     Vec2(0.5, 0.5), nullptr},
    {ECharName::SCV, ECharAct::Move, ECharDir::S, "Plist/SCV.plist", "SCV/Move/9/0009.png", 1, 1, (1.f / 1),     Vec2(0.5, 0.5), nullptr},
    {ECharName::SCV, ECharAct::Move, ECharDir::SSW, "Plist/SCV.plist", "SCV/Move/10/0010.png", 1, 1, (1.f / 1),     Vec2(0.5, 0.5), nullptr},
    {ECharName::SCV, ECharAct::Move, ECharDir::SW, "Plist/SCV.plist", "SCV/Move/11/0011.png", 1, 1, (1.f / 1),     Vec2(0.5, 0.5), nullptr},
    {ECharName::SCV, ECharAct::Move, ECharDir::WSW, "Plist/SCV.plist", "SCV/Move/12/0012.png", 1, 1, (1.f / 1),     Vec2(0.5, 0.5), nullptr},
    {ECharName::SCV, ECharAct::Move, ECharDir::W, "Plist/SCV.plist", "SCV/Move/13/0013.png", 1, 1, (1.f / 1),     Vec2(0.5, 0.5), nullptr},
    {ECharName::SCV, ECharAct::Move, ECharDir::WNW, "Plist/SCV.plist", "SCV/Move/14/0014.png", 1, 1, (1.f / 1),     Vec2(0.5, 0.5), nullptr},
    {ECharName::SCV, ECharAct::Move, ECharDir::NW, "Plist/SCV.plist", "SCV/Move/15/0015.png", 1, 1, (1.f / 1),     Vec2(0.5, 0.5), nullptr},
    {ECharName::SCV, ECharAct::Move, ECharDir::NNW, "Plist/SCV.plist", "SCV/Move/16/0016.png", 1, 1, (1.f / 1),     Vec2(0.5, 0.5), nullptr},
};


AnimInfo g_AnimInfo_Select_Idle[] = {{ECharName::Select, ECharAct::Move, ECharDir::Face, "Plist/Select.plist",
                                      "Select/%04d.png", 1, 2, (1.f / 2), Vec2(0.5, 0.5), nullptr}
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
    /// farmer
    case ECharName::Select:
        return g_AnimInfo_Select_Idle[0];
    case ECharName::Marine:
        switch (action)
        {
        case ECharAct::Idle:
            for (int i = 0; i < 16; i++)
            {
                if (g_AnimInfo_Marin_Idle[i].dir == dir)
                    return g_AnimInfo_Marin_Idle[i];
            }
            break;
        case ECharAct::Move:
            for (int i = 0; i < 16; i++)
            {
                if (g_AnimInfo_Marin_Move[i].dir == dir)
                    return g_AnimInfo_Marin_Move[i];
            }
            break;
        default:
            break;
        }
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
                if (g_AnimInfo_SCV_Idle[i].dir == dir)
                    return g_AnimInfo_SCV_Idle[i];
            }
            break;
        }break;
    }
}
