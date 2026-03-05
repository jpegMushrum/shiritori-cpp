#include <vector>

#include "games_repo.hpp"

std::vector<Game> GamesRepo::getActiveGames()
{
    return std::vector<Game>(2, Game(123));
}