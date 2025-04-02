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
