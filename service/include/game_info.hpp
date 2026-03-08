#pragma once

#include <iostream>

using ull = unsigned long long;

class GameInfo
{
  public:
    GameInfo(ull, int, int, int);

    ull id;
    int wordsCount;
    int playersCount;
    int playersCapacity;

    friend std::ostream& operator<<(std::ostream&, const GameInfo&);
};