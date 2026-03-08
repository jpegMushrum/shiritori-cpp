#pragma once

#include <atomic>
#include <functional>
#include <map>
#include <memory>
#include <shared_mutex>
#include <string>
#include <vector>

#include "game_info.hpp"
#include "game_session.hpp"
#include "handle_word_status.hpp"
#include "task_queue.hpp"

using ull = unsigned long long;

class GamesController
{
  public:
    GamesController(std::shared_ptr<TaskQueue>);

    void StartNewGame(std::function<void(ull)>);
    void HandleWord(ull, ull, std::string, std::function<void(HandleWordStatus)>);
    void GetActiveGames(std::function<void(std::vector<GameInfo>)>);

  private:
    std::unordered_map<ull, std::shared_ptr<GameSession>> activeGames_;
    std::shared_ptr<TaskQueue> taskQueue_;
    ull nextGameId_;

    mutable std::shared_mutex mu_;
};