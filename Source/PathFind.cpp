#include "pch.h"
#include "PathFind.h"
#include <iostream>
#include "ComFunction.h"
#include <chrono>
#include <time.h>
#include <cmath>
#include <stdarg.h>



PathFind::PathFind(int width, int height)
{
    mColMap = std::make_shared<jpspath::CollisionMap>();

    int32_t GridWidth = width;
    int32_t GridHeight = height;

    mWidth  = width;
    mHeight = height;

    mColMap->Create(GridWidth, GridHeight);

}

void PathFind::DefaultSetting(ax::TMXLayer* wall)
{
    for (int i = 0; i < mHeight; i++)
    {
        for (int j = 0; j < mWidth; j++)
        {
            if (wall->getTileAt(ax::Vec2(j, mHeight - 1 - i)))
            {
                auto value = wall->getProperty("wall");
                if (value.asBool())
                   mColMap->SetAt(j, i);
                else
                    mColMap->ClrAt(j, i);
            }
        }
    }
}

void PathFind::DebugMap()
{
    for (int i = 0; i < mHeight; i++)
    {
        for (int j = 0; j < mWidth; j++)
        {
            if (mColMap->IsCollision(j, i))
            {
                printf("*");
            }
            else
            {
                printf("0");
            }
        }
        printf("\n");
    }
}

void PathFind::update(float delta)
{
    Counting = 0;
}

bool PathFind::Enter()
// 골로 추가할것
{
    if (Counting < 3)
    {
        Counting++;
        return true;
    }
    else
        return false;
}

void PathFind::SetTileActorPhysics(ax::Vec2 actorPos, ax::Vec2 actorSize)
{
    auto ap = actorPos;
    auto as = actorSize;


    int spX, spY;
    spX = ap.x - (as.x / 2);
    spY = ap.y + (as.y / 2);

    spX = spX / 16;
    spY = spY / 16;

    int epX, epY;
    epX = ap.x + (as.x / 2);
    epY = ap.y - (as.y / 2);

    epX = epX / 16;
    epY = epY / 16;




    for (int i = spX; i <= epX; i++)
    {
        for (int j = epY; j <= spY; j++)
        {
            mColMap->SetAt(i, j);
        }
    }


    printf("설치끝~");



}

void PathFind::ClrTileActorPhysics(ax::Vec2 actorPos, ax::Vec2 actorSize)
{
    auto ap = actorPos;
    auto as = actorSize;

    int spX, spY;
    spX = ap.x - (as.x / 2);
    spY = ap.y + (as.y / 2);

    spX = spX / 16;
    spY = spY / 16;

    int epX, epY;
    epX = ap.x + (as.x / 2);
    epY = ap.y - (as.y / 2);

    epX = epX / 16;
    epY = epY / 16;

    for (int i = spX; i <= epX; i++)
    {
        for (int j = epY; j <= spY; j++)
        {
            mColMap->ClrAt(i, j);
        }
    }
}

ax::Vec2 PathFind::FindEmptyTileNearActor(ax::Vec2 sPos, ax::Vec2 ePos)
{
    auto sp = sPos;
    auto ep = ePos;


    auto findPos = sp - ep;

    float fx = std::abs(findPos.x);
    float fy = std::abs(findPos.y);

    if (fx >= fy)
    {
        if (findPos.x > 0)
        {
            int32_t pos = mColMap->GetOpenValue(ePos.x / 16, ePos.y / 16, true, true);
            return ax::Vec2(pos*16,ePos.y);
        }
        else
        {
            int32_t pos = mColMap->GetOpenValue(ePos.x / 16, ePos.y / 16, true, false);
            return ax::Vec2(pos * 16, ePos.y);
        }
    }
    else
    {
        if (findPos.y > 0)
        {
            int32_t pos = mColMap->GetOpenValue(ePos.x / 16, ePos.y / 16, false, true);
            return ax::Vec2(ePos.x, pos * 16);
        }
        else
        {
            int32_t pos = mColMap->GetOpenValue(ePos.x / 16, ePos.y / 16, false, false);
            return ax::Vec2(ePos.x, pos * 16);
        }
    }
    return ax::Vec2::ZERO;
}

std::list<ax::Vec2> PathFind::GetTargetList(ax::Vec2 start, ax::Vec2 dest)
{
    auto resultNode = PathSearch(start, dest);

    std::list<ax::Vec2> targetList;

    for (auto t : resultNode)
    {
        ax::Vec2 pos;
        pos.x = (float)t.m_x * 16;
        pos.y = (float)t.m_y * 16;
        targetList.push_back(pos);
    }
    return targetList;
}

std::list<jpspath::Coord> PathFind::PathSearch(ax::Vec2 start, ax::Vec2 dest)
{
    if (!mColMap)
        return std::list<jpspath::Coord> ();


    std::list<jpspath::Coord> ResultNodes;
    jpspath::Path jps;
    
    jps.Init(mColMap);

    int32_t sx = start.x / 16;
    int32_t sy = start.y / 16;
    int32_t ex = dest.x / 16;
    int32_t ey = dest.y / 16;

    jps.Search(sx, sy, ex, ey, ResultNodes);
    return ResultNodes;
}
