#include "pch.h"
#include "2DGeometry.h"


#define MIN_RECT_WIDTH 5.f;
#define MIN_RECT_HEIGHT 5.f


bool isContacted(AABOX blue, AABOX red)
{
    if ((blue.right > red.left) && (red.right > blue.left) && (blue.top > red.bottom) && (red.top > blue.bottom))
        return true;
    else
        return false;
}

ax::Vec2 GetZeroPointInRect(ax::Vec2 sPos, ax::Vec2 ePos)
{
    
    float sx = std::min(sPos.x, ePos.x);
    float sy = std::min(sPos.y, ePos.y);

    ax::Vec2 pos(sx, sy);

    return pos;

}

float GetRectWidth(ax::Vec2 sPos, ax::Vec2 ePos)
{
    float bx = std::max(sPos.x, ePos.x);
    float sx = std::min(sPos.x, ePos.x);

    if (length(sPos, ePos) < 10)
    {
        return MIN_RECT_WIDTH;
    }
    else
    {
        return bx - sx;
    }
    

    return bx - sx;
}

float GetRectHeight(ax::Vec2 sPos, ax::Vec2 ePos)
{
    float by = std::max(sPos.y, ePos.y);
    float sy = std::min(sPos.y, ePos.y);

    if (length(sPos, ePos) < 10)
    {
        return MIN_RECT_HEIGHT;
    }
    else
    {
        return by - sy;
    }

    return by - sy;
}

float length(ax::Vec2 v1, ax::Vec2 v2)
{
    float dx = v2.x - v1.x;
    float dy = v2.y - v1.y;

    return sqrt(dx * dx + dy * dy);
}

ax::Vec2 GetRandomPosToBuild(BuildingSize size, ax::Vec2 pos)
{
    int idx;
    srand(time(NULL));
    ax::Vec2 Pos;

    switch (size)
    {
    case BuildingSize::Small:
    {
    }
        break;
    case BuildingSize::Middle:
        break;
    case BuildingSize::Big:
    {
        idx = rand() % 7 - 3;
        Pos.x = (float)idx * 16;
        idx   = rand() % 7 - 3;
        Pos.y = (float)idx * 16;
        return Pos;
    }
        break;
    default:
        break;
    }

    return ax::Vec2(0,0);
}

