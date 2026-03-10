#pragma once

#include <algorithm>
#include <functional>
#include <memory>
#include <mutex>
#include <string>
#include <unordered_set>
#include <vector>

#include "game.hpp"
#include "game_session_info.hpp"
#include "games_repo.hpp"
#include "handle_word_status.hpp"
#include "jisho.hpp"
#include "player_score.hpp"
#include "user.hpp"
#include "word.hpp"

using ull = unsigned long long;

class GameSession
{
  public:
    GameSession(ull, std::shared_ptr<IDictionary>, std::shared_ptr<GamesRepo>);
    ~GameSession();

    void addUser(ull);
    HandleWordStatus handleWord(ull, const std::string&);
    void stopGame();

    GameSessionInfo GetInfo();

  private:
    std::unordered_set<PlayerScore> players_;
    std::vector<Word> words_;
    void saveStats();

    std::shared_ptr<IDictionary> dict_;
    std::shared_ptr<GamesRepo> repo_;

    bool stop_;
    std::mutex mu_;
    GameSessionInfo info_;
};