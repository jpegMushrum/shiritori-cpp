#pragma once

using ull = unsigned long long;

class Game
{
  public:
    Game(ull, bool);

    ull id;
    bool active;
};