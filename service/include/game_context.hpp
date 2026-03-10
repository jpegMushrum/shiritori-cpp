#pragma once

#include <iostream>

using ull = unsigned long long;

class GameContext
{
  public:
    GameContext();
    GameContext(ull, int, int);

    ull id;
    int wordsCount;
    int playersCount;

    friend std::ostream& operator<<(std::ostream&, const GameContext&);
};