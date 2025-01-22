#include "pch.h"
#include "2DGeometry.h"

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

    return bx - sx;
}

float GetRectHeight(ax::Vec2 sPos, ax::Vec2 ePos)
{
    float by = std::max(sPos.y, ePos.y);
    float sy = std::min(sPos.y, ePos.y);

    return by - sy;
}

