#pragma once

using ull = unsigned long long;

class GameInfo
{
  public:
    GameInfo(ull, ull, int, int);

    ull gameId;
    ull userId;
    int words;
    int place;
};