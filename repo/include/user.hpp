#pragma once

#include <string>

using ull = unsigned long long;

class User
{
  public:
    User();
    User(ull, std::string);

    ull id;
    std::string nickname;
};