#include <iostream>

#include "game_info.hpp"

using ull = unsigned long long;

GameInfo::GameInfo(ull id) : id(id) {}

GameInfo::GameInfo() {}

std::ostream& operator<<(std::ostream& out, const GameInfo& gi)
{
    out << gi.id;
    return out;
}