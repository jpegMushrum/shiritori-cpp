#include <iostream>

#include "game_info.hpp"

using ull = unsigned long long;

GameInfo::GameInfo(ull id, int wordsCount, int playersCount, int playersCapacity)
    : id(id), wordsCount(wordsCount), playersCount(playersCount), playersCapacity(playersCapacity)
{
}

std::ostream& operator<<(std::ostream& out, const GameInfo& gi)
{
    out << gi.id << " " << gi.wordsCount << " " << gi.playersCount << " " << gi.playersCapacity;
    return out;
}