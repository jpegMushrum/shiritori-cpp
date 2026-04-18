#include "word_info.hpp"

WordInfo::WordInfo(std::string kanji, std::vector<std::string> readings,
                   std::set<std::string> partsOfSpeach, std::vector<std::string> meanings)
    : kanji(kanji), meanings(meanings),
      readings(std::vector<std::string>(readings.begin(), readings.end())),
      partsOfSpeach(std::set<std::string>(partsOfSpeach.begin(), partsOfSpeach.end()))
{
}