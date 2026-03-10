#pragma once

#include <set>
#include <string>

class Word
{
  public:
    Word();

    std::string kanji;
    std::set<std::string> readings;
    std::set<std::string> partsOfSpeach;

    std::string meaning;
};