#pragma once


#pragma pack(push,1)

struct PK_Head
{
    char UniqueID          = 12;
    unsigned short dataLen = 0;
};


struct PK_Data
{
    short ClientID = -1;
    char input  = 0;
    ax::Vec2 pos;
};

#pragma pack(pop)

//    1 : 77
//    2 : 78
//    3 : 79
//    R : 141
//    L : 135


void SendPK_Data(int command, ax::Vec2 pos);

