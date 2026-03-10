#pragma once

#include <iostream>

using ull = unsigned long long;

class GameSessionInfo
{
  public:
    GameSessionInfo();
    GameSessionInfo(ull, int, int);

    ull id;
    int wordsCount;
    int playersCount;

    friend std::ostream& operator<<(std::ostream&, const GameSessionInfo&);
};