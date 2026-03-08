#include "game_session.hpp"

using ull = unsigned long long;

GameSession::GameSession(ull id) : info_(id, 0, 0, 16) {}

void GameSession::addUser(ull id)
{
    std::lock_guard lock(mu_);

    players_.emplace(id);
    info_.playersCount++;
}

HandleWordStatus GameSession::handleWord(ull id, const std::string& word)
{
    return HandleWordStatus::ERROR;
}

GameInfo GameSession::GetInfo()
{
    std::lock_guard lock(mu_);
    return info_;
}