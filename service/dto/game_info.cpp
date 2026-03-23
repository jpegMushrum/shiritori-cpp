#include "game_info.hpp"

GameInfo::GameInfo() : gameId(0), userId(0), words(0), place(0) {}

GameInfo::GameInfo(ull gameId, ull userId, int words, int place)
    : gameId(gameId), userId(userId), words(words), place(place)
{
}