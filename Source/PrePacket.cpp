#include "pch.h"
#include "PrePacket.h"


void SendPK_Data(int command, ax::Vec2 pos)
{
    PK_Data data;
    data.ClientID = TcpClient::get()->GetID();
    data.input    = command;
    data.pos      = pos;
    TcpClient::get()->SendMessageToServer(data);
}
