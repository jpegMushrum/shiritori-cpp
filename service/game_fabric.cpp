#include "game_fabric.hpp"

GameFabric::GameFabric(std::shared_ptr<IDictionary> dict, std::shared_ptr<GamesRepo> repo)
    : dict_(dict), repo_(repo)
{
}

std::shared_ptr<GameSession> GameFabric::createGame(ull gameId)
{
    return std::make_shared<GameSession>(gameId, dict_, repo_);
}