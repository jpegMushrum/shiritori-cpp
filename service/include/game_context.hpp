#pragma once

#include <boost/locale.hpp>
#include <iostream>
#include <string>

using ull = unsigned long long;

class GameContext
{
  public:
    GameContext();
    GameContext(ull, int, int, ull, char32_t);

    ull id;
    int wordsCount;
    int playersCount;

    ull adminId;
    ull lastPlayerId;

    char32_t lastKana;

    friend std::ostream& operator<<(std::ostream&, const GameContext&);
};