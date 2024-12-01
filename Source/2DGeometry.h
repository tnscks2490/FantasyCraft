#pragma once


struct AABOX
{
    int left;
    int right;
    int top;
    int bottom;
};


bool isContacted(AABOX blue,AABOX red)
{
    if ((blue.right > red.left) &&
        (red.right > blue.left) &&
        (blue.top > red.bottom) &&
        (red.top > blue.bottom))
        return true;
    else
        return false;
}
