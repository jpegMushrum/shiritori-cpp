#pragma once

#include <iostream>

using ull = unsigned long long;

class UserInfo
{
  public:
    UserInfo(ull);

    ull id;

    friend std::ostream& operator<<(std::ostream&, const UserInfo&);
};