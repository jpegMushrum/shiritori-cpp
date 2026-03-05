#pragma once

#include <iostream>

using ull = unsigned long long;

class GameInfo
{
  public:
    GameInfo(ull);
    GameInfo();

    ull id;

    friend std::ostream& operator<<(std::ostream&, const GameInfo&);
};