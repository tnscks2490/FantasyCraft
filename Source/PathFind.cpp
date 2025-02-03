#include "pch.h"
#include "PathFind.h"
#include <iostream>
#include <chrono>
#include <time.h>
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
                printf("1");
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
