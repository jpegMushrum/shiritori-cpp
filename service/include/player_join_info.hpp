#pragma once

#include "word.hpp"

#include <vector>

struct PlayerJoinInfo
{
    char32_t lastKana;
    std::vector<Word> usedWords;
};