#include "pch.h"
#include "ComFunction.h"

std::string_view IntToStringView(int num)
{
    std::string str = std::to_string(num);

    return std::string_view(str);
}

std::string_view FloatToStringView(float num)
{
    std::string str = std::to_string(num);

    return std::string_view(str);
}

std::string NumSlashNumToString(int num1, int num2)
{

    std::string str;
    str = std::to_string(num1) + "/" +std::to_string(num2);

    return str;
}

int GetCreateCommand(ActorType type)
{
    int command = 0;
    switch (type)
    {
    case ActorType::SCV:        command = 100;        return command;
    case ActorType::Marine:        command = 101;        return command;
    case ActorType::CommandCenter:        command = 102;        return command;
    case ActorType::SupplyDepot:        command = 103;        return command;
    case ActorType::Barrack:        command = 104;        return command;
    }
    return 0;
}
