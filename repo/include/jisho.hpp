#pragma once

#include <curl/curl.h>
#include <nlohmann/json.hpp>

#include "word.hpp"

class JishoDict
{
  public:
    JishoDict();
    Word SearchWord(const std::string&);

  private:
    static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp);
};