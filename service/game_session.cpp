#include <future>

#include "game_session.hpp"

using ull = unsigned long long;

GameSession::GameSession(ull id, std::shared_ptr<IDictionary> dict, std::shared_ptr<GamesRepo> repo)
    : info_(id, 0, 0), dict_(dict), repo_(repo), stop_(false)
{
}

void GameSession::stopGame()
{
    std::lock_guard lock(mu_);
    stop_ = true;
}

GameSession::~GameSession()
{
    saveStats();
}

void GameSession::saveStats()
{
    std::lock_guard lock(mu_);

    std::vector<PlayerScore> players = std::vector(players_.begin(), players_.end());
    std::vector<Game> gameParts;

    std::sort(players.begin(), players.end(), PlayerScore::psCmp);

    int place = 1;
    for (auto& usr : players)
    {
        gameParts.push_back(Game(info_.id, usr.userId, usr.score, place));
        ++place;
    }

    repo_->putGame(gameParts);
}

void GameSession::addUser(ull id)
{
    std::lock_guard lock(mu_);

    PlayerScore player;
    player.userId = id;

    players_.emplace(player);
    info_.playersCount++;
}

HandleWordStatus GameSession::handleWord(ull id, const std::string& word)
{
    std::lock_guard lock(mu_);
    if (stop_)
    {
        return HandleWordStatus::GAME_STOPPED;
    }

    std::promise<std::vector<Word>> promise;
    auto future =
        std::async(std::launch::async, [this, word]() { return dict_->SearchWord(word); });

    // тут будут проверки

    auto response = future.get();
    return HandleWordStatus::OK;
}

GameSessionInfo GameSession::GetInfo()
{
    std::lock_guard lock(mu_);
    return info_;
}