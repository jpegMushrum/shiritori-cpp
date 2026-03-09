#pragma once

#include <string>

using ull = unsigned long long;

class User
{
  public:
    User();
    User(ull, std::string, double);

    ull id;
    std::string nickname;
    double words_awg;
};