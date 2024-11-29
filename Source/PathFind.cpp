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
                auto value = wall->getProperty("Wall");
                if (value.asBool())
                   mColMap->SetAt(j, i);
                else
                    mColMap->ClrAt(j, i);
            }
        }
    }
}
