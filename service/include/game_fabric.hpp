#pragma once

#include <memory>

#include "game_session.hpp"
#include "jisho.hpp"

using ull = unsigned long long;

class GameFabric
{
  public:
    std::shared_ptr<GameSession> createGame(ull);

    GameFabric(std::shared_ptr<JishoDict>);

  private:
    std::shared_ptr<JishoDict> dict_;
};