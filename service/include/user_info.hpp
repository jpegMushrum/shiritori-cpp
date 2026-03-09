#pragma once

#include <iostream>

using ull = unsigned long long;

class UserInfo
{
  public:
    UserInfo(ull, std::string, double);

    ull id;
    std::string nickname;
    double words_awg;

    friend std::ostream& operator<<(std::ostream&, const UserInfo&);
};