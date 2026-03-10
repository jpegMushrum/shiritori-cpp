#include <iostream>

#include "game_session_info.hpp"

using ull = unsigned long long;

GameSessionInfo::GameSessionInfo() : id(0), wordsCount(0), playersCount(0) {}

GameSessionInfo::GameSessionInfo(ull id, int wordsCount, int playersCount)
    : id(id), wordsCount(wordsCount), playersCount(playersCount)
{
}

std::ostream& operator<<(std::ostream& out, const GameSessionInfo& gi)
{
    out << gi.id << " " << gi.wordsCount << " " << gi.playersCount;
    return out;
}