#pragma once

#include <mutex>
#include <string>
#include <unordered_set>
#include <vector>

#include "game_info.hpp"
#include "handle_word_status.hpp"
#include "user.hpp"
#include "word.hpp"

using ull = unsigned long long;

class GameSession
{
  public:
    void addUser(ull);
    HandleWordStatus handleWord(ull, const std::string&);

    GameInfo GetInfo();
    GameSession(ull);

  private:
    std::unordered_set<ull> players_;
    std::vector<Word> words_;

    std::mutex mu_;
    GameInfo info_;
};